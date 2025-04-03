#include "queue.h"
#include "tile_game.h"


void enqueue(struct queue *q, struct game_state state) 
{
  uint64_t encoded = serialize(state);
  insert_at_tail(&q->data, encoded);
}

struct game_state dequeue(struct queue *q) 
{ 
  uint64_t encoded = remove_from_head(&q->data);
  return(deserialize(encoded)); 
}

int number_of_moves(struct game_state start) 
{ 
}
