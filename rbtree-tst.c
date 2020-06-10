/*
 * =============================================================================
 *
 *       Filename:  rbtree-tst.c
 *
 *    Description:  rbtree testcase.
 *
 *        Created:  09/02/2012 11:39:34 PM
 *
 *         Author:  Fu Haiping (forhappy), haipingf@gmail.com
 *        Company:  ICT ( Institute Of Computing Technology, CAS )
 *
 * =============================================================================
 */

#include "rbtree.h"
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct over_speed_node{
	uint32_t bandwidth_id;
	uint64_t rx_over_speed;
	uint64_t tx_over_speed;
	uint8_t is_limited;
}over_speed_node_t;

struct mynode {
  	struct rb_node node;
  	over_speed_node_t *over_speed_data;
};

struct rb_root mytree = RB_ROOT;

int max(uint64_t a, uint64_t b){
	return a>b ? a : b;
 }


static int comp_help(uint64_t ar, uint64_t at, uint64_t br, uint64_t bt)
{
	uint64_t Max_value = max(ar, max(at, max(br, bt)));
	if(Max_value == max(ar, at) && Max_value == max(br, bt))
	{
		return 0;
	} 
	else if(Max_value == max(ar, at))
	{
		return 1;
	}
	else
	{
		return -1;
	} 
}


// compare function for sort
static int comp(over_speed_node_t *nodea,	over_speed_node_t *nodeb)
{
	if((nodea->is_limited == 0) && (nodeb->is_limited == 0)) 
	{
		return comp_help(nodea->rx_over_speed, nodea->tx_over_speed, \
		nodeb->rx_over_speed, nodeb->tx_over_speed);
	}
  	else if(nodea->is_limited || nodeb->is_limited)
	{
		return nodea->is_limited ? -1 : 1;
	}
	else   //都已经派发了meter则如何排序？
		return (nodea->bandwidth_id == nodeb->bandwidth_id) ? 0: (nodea->bandwidth_id < nodeb->bandwidth_id); 
}



struct mynode * my_search(struct rb_root *root, over_speed_node_t *over_speed_data)
{
  	struct rb_node *node = root->rb_node;

  	while (node) {
  		struct mynode *data = container_of(node, struct mynode, node);
		int result;

		result = comp(over_speed_data, data->over_speed_data);

		if (result < 0)
  			node = node->rb_left;
		else if (result > 0)
  			node = node->rb_right;
		else
  			return data;
	}
	return NULL;
}

int my_insert(struct rb_root *root, struct mynode *data)
{
  	struct rb_node **new = &(root->rb_node), *parent = NULL;

  	/* Figure out where to put new node */
  	while (*new) {
  		struct mynode *this = container_of(*new, struct mynode, node);
  		int result = comp(data->over_speed_data, this->over_speed_data);

		parent = *new;
  		if (result < 0)
  			new = &((*new)->rb_left);
  		else if (result > 0)
  			new = &((*new)->rb_right);
  		else
  			return 0;
  	}

  	/* Add new node and rebalance tree. */
  	rb_link_node(&data->node, parent, new);
  	rb_insert_color(&data->node, root);

	return 1;
}

void my_free(struct mynode *node)
{
	if (node != NULL) {
		if (node->over_speed_data != NULL) {
			free(node->over_speed_data);
			node->over_speed_data = NULL;
		}
		free(node);
		node = NULL;
	}
}

#define NUM_NODES 10

int main()
{

	struct mynode *mn[NUM_NODES];

	/* *insert */
	int i = 0;
	//printf("insert node from 1 to NUM_NODES(32): \n");
	for (; i < NUM_NODES; i++) {
		mn[i] = (struct mynode *)malloc(sizeof(struct mynode));
		mn[i]->over_speed_data = (over_speed_node_t *)malloc(sizeof(over_speed_node_t));
		mn[i]->over_speed_data->bandwidth_id = 1000+i;
		mn[i]->over_speed_data->tx_over_speed = 20-i;
		mn[i]->over_speed_data->rx_over_speed = 20-i;
		mn[i]->over_speed_data->is_limited = i>5? 1:0;
		my_insert(&mytree, mn[i]);
	}
	
	/* *print all node */
	struct rb_node *node;
	printf("search all nodes: \n");
	for (node = rb_first(&mytree); node; node = rb_next(node))
	{
		printf("The rb_node : %u,%lu,%lu,%u\n", \
		rb_entry(node, struct mynode, node)->over_speed_data->bandwidth_id, \
		rb_entry(node, struct mynode, node)->over_speed_data->tx_over_speed, \
		rb_entry(node, struct mynode, node)->over_speed_data->rx_over_speed, \
		rb_entry(node, struct mynode, node)->over_speed_data->is_limited);
	}


	/* *delete */
	printf("delete bandwidth_id 1002: \n");
	over_speed_node_t *key = (over_speed_node_t *)malloc(sizeof(over_speed_node_t));
	key->bandwidth_id = 1002;
	key->tx_over_speed = 18;
	key->rx_over_speed = 18;
	key->is_limited = 0;
	struct mynode *data = my_search(&mytree, key);
	if (data) {
		rb_erase(&data->node, &mytree);
		my_free(data);
	}

	/* *delete again*/
	printf("delete node 1006: \n");
	key->bandwidth_id = 1006;
	key->tx_over_speed = 14;
	key->rx_over_speed = 14;
	key->is_limited = 1;
	data = my_search(&mytree, key);
	if (data) {
		rb_erase(&data->node, &mytree);
		my_free(data);
	}

	/* *delete once again*/
	printf("delete node 15: \n");
	data = my_search(&mytree, "15");
	if (data) {
		rb_erase(&data->node, &mytree);
		my_free(data);
	}

	/* *search again*/
	printf("search again:\n");
	for (node = rb_first(&mytree); node; node = rb_next(node))
	{
		printf("The rb_node : %u,%lu,%lu,%u\n", \
		rb_entry(node, struct mynode, node)->over_speed_data->bandwidth_id, \
		rb_entry(node, struct mynode, node)->over_speed_data->tx_over_speed, \
		rb_entry(node, struct mynode, node)->over_speed_data->rx_over_speed, \
		rb_entry(node, struct mynode, node)->over_speed_data->is_limited);
	}
	return 0;
}


