
#include "over_speed_rbtree.h"


#define NUM_NODES 10

int main()
{

	struct over_speed_node_info *mn[NUM_NODES];

	/* *insert */
	int i = 0;
	//printf("insert node from 1 to NUM_NODES(32): \n");
	for (; i < NUM_NODES; i++) {
		mn[i] = (struct over_speed_node_info *)malloc(sizeof(struct over_speed_node_info));
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
		rb_entry(node, struct over_speed_node_info, node)->over_speed_data->bandwidth_id, \
		rb_entry(node, struct over_speed_node_info, node)->over_speed_data->tx_over_speed, \
		rb_entry(node, struct over_speed_node_info, node)->over_speed_data->rx_over_speed, \
		rb_entry(node, struct over_speed_node_info, node)->over_speed_data->is_limited);
	}


	/* *delete */
	printf("delete bandwidth_id 1002: \n");
	over_speed_node_t *key = (over_speed_node_t *)malloc(sizeof(over_speed_node_t));
	key->bandwidth_id = 1002;
	key->tx_over_speed = 18;
	key->rx_over_speed = 18;
	key->is_limited = 0;
	struct over_speed_node_info *data = my_search(&mytree, key);
	if (data) {
		rb_erase(&data->node, &mytree);
		my_free(data);
	}

	/* *delete again*/
	printf("delete bandwidth_id 1006: \n");
	key->bandwidth_id = 1006;
	key->tx_over_speed = 14;
	key->rx_over_speed = 14;
	key->is_limited = 1;
	data = my_search(&mytree, key);
	if (data) {
		rb_erase(&data->node, &mytree);
		my_free(data);
	}


	/* *search again*/
	printf("search again:\n");
	for (node = rb_first(&mytree); node; node = rb_next(node))
	{
		printf("The rb_node : %u,%lu,%lu,%u\n", \
		rb_entry(node, struct over_speed_node_info, node)->over_speed_data->bandwidth_id, \
		rb_entry(node, struct over_speed_node_info, node)->over_speed_data->tx_over_speed, \
		rb_entry(node, struct over_speed_node_info, node)->over_speed_data->rx_over_speed, \
		rb_entry(node, struct over_speed_node_info, node)->over_speed_data->is_limited);
	}
	return 0;
}