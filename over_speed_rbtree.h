#ifndef	_OVER_SPEED_RBTREE_H
#define	_OVER_SPEED_RBTREE_H

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include "rbtree.h"

typedef struct over_speed_node{
	uint32_t bandwidth_id;
	uint64_t rx_over_speed;
	uint64_t tx_over_speed;
	uint8_t is_limited;
}over_speed_node_t;

struct over_speed_node_info {
  	struct rb_node node;
  	over_speed_node_t *over_speed_data;
};



extern int comp_help(uint64_t ar, uint64_t at, uint64_t br, uint64_t bt);
extern int comp(over_speed_node_t *nodea,	over_speed_node_t *nodeb);
extern struct over_speed_node_info * my_search(struct rb_root *root, over_speed_node_t *over_speed_data);
extern int my_insert(struct rb_root *root, struct over_speed_node_info *data);
extern void my_free(struct over_speed_node_info *node);



#endif
