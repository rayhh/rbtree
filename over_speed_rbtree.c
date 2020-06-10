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

#include "over_speed_rbtree.h"


int max(uint64_t a, uint64_t b){
	return a>b ? a : b;
 }


int comp_help(uint64_t ar, uint64_t at, uint64_t br, uint64_t bt)
{
	uint64_t Max_value = max(ar, max(at, max(br, bt)));
	if(Max_value == max(ar, at) && Max_value == max(br, bt))
	{
		return 0;
	} 
	else if(Max_value == max(ar, at))
	{
		return -1;
	}
	else
	{
		return 1;
	} 
}


// compare function for sort
int comp(over_speed_node_t *nodea,	over_speed_node_t *nodeb)
{
	if((nodea->is_limited == 0) && (nodeb->is_limited == 0)) 
	{
		return comp_help(nodea->rx_over_speed, nodea->tx_over_speed, \
		nodeb->rx_over_speed, nodeb->tx_over_speed);
	}
  	else if((nodea->is_limited && !nodeb->is_limited) || (!nodea->is_limited && nodeb->is_limited))
	{
		return nodea->is_limited ? 1 : -1;
	}
	else   //都已经派发了meter则如何排序？
		return comp_help(nodea->rx_over_speed, nodea->tx_over_speed, \
		nodeb->rx_over_speed, nodeb->tx_over_speed);
}



struct over_speed_node_info * my_search(struct rb_root *root, over_speed_node_t *over_speed_data)
{
  	struct rb_node *node = root->rb_node;

  	while (node) {
  		struct over_speed_node_info *data = container_of(node, struct over_speed_node_info, node);
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

int my_insert(struct rb_root *root, struct over_speed_node_info *data)
{
  	struct rb_node **new = &(root->rb_node), *parent = NULL;

  	/* Figure out where to put new node */
  	while (*new) {
  		struct over_speed_node_info *this = container_of(*new, struct over_speed_node_info, node);
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

void my_free(struct over_speed_node_info *node)
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




