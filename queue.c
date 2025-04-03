#include "queue.h"
#include "tile_game.h"
#define MAX_SEEN 1000003

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
  seen = calloc(MAX_SEEN, sizeof(bool));
  free(seen);
  free_list(q.data);
  return(-1); 
}
