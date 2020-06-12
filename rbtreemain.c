
#include "over_speed_rbtree.h"


#define NUM_NODES 5
struct rb_root mytree = RB_ROOT;

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
	printf("delete all \n");
	for(i=0;i<NUM_NODES;i++)
	{
		over_speed_node_t *key = (over_speed_node_t *)malloc(sizeof(over_speed_node_t));
		key->bandwidth_id = 1000+i;
		key->tx_over_speed = 20-i;
		key->rx_over_speed = 20-i;
		key->is_limited = 0;
		struct over_speed_node_info *data = my_search(&mytree, key);
		if (data) {
			rb_erase(&data->node, &mytree);
			my_free(data);
		}
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

	struct over_speed_node_info *nw[3];

	for(i=0;i<3;i++){
		nw[i] = (struct over_speed_node_info *)malloc(sizeof(struct over_speed_node_info));
		nw[i]->over_speed_data = (over_speed_node_t *)malloc(sizeof(over_speed_node_t));
		nw[i]->over_speed_data->bandwidth_id = 3000+i;
		nw[i]->over_speed_data->tx_over_speed = 100+i;
		nw[i]->over_speed_data->rx_over_speed = 100+i;
		nw[i]->over_speed_data->is_limited = i>5? 1:0;
		my_insert(&mytree, nw[i]);		
	}

	printf("search last:\n");
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