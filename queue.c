#include "queue.h"
#include "tile_game.h"


void enqueue(struct queue *q, struct game_state state) 
{
  uint64_t encoded = serialize(state);

  if(q->data.head == NULL)
  {
    insert_at_head(&q->data, encoded);
  }

  else
  {
    insert_at_tail(&q->data, encoded);
  }

}

struct game_state dequeue(struct queue *q) 
{ 
  uint64_t encoded;
   
  if(q->data.head != NULL && q->data.head->next == NULL)
  {
    encoded = remove_from_tail(&q->data);
  }

  else
  {
    encoded = remove_from_head(&q->data);
  }

  return(deserialize(encoded)); 
}

int number_of_moves(struct game_state start) 
{ 
    struct queue q;
    q.data.head = NULL;

    struct linked_list moves;
    moves.head = NULL;

    uint64_t visited[100000];
    int vis_cnt = 0;

    enqueue(&q, start);
    insert_at_tail(&moves, 0);

    visited[vis_cnt++] = serialize(start);

    while(q.data.head != NULL)
    {
        struct game_state current = dequeue(&q);
        int moves_so_far = (int)remove_from_head(&moves);

        int goal = 1;
        for(int i = 0; i < 4; i++)
        {
            for(int j = 0; j < 4; j++)
            {
                int expected = i * 4 + j + 1;
                if(i == 3 && j == 3)
                {
                    if(current.tiles[i][j] != 0)
                    {
                        goal = 0;
                        break;
                    }
                }
                else
                {
                    if(current.tiles[i][j] != expected)
                    {
                        goal = 0;
                        break;
                    }
                }
            }

            if(!goal)
            {
                break;
            }
        }

        if(goal)
        {
            free_list(q.data);
            free_list(moves);
            return(moves_so_far);
        }

        struct game_state next[4];
        int count = 0;

        for(int dir = 0; dir < 4; dir++)
        {
            struct game_state temp = current;

            if(dir == 0 && temp.empty_row < 3)
            {
                move_up(&temp);
                next[count++] = temp;
            }
            else if(dir == 1 && temp.empty_row > 0)
            {
                move_down(&temp);
                next[count++] = temp;
            }
            else if(dir == 2 && temp.empty_col < 3)
            {
                move_left(&temp);
                next[count++] = temp;
            }
            else if(dir == 3 && temp.empty_col > 0)
            {
                move_right(&temp);
                next[count++] = temp;
            }

        }

        for(int i = 0; i < count; i ++)
        {
            uint64_t serial = serialize(next[i]);
            int seen = 0;

            for(int j = 0; j < vis_cnt; j++)
            {
                if(visited[j] == serial)
                {
                    seen = 1;
                    break;
                }

            }

            if(!seen)
            {
                visited[vis_cnt++] = serial;
                enqueue(&q, next[i]);
                insert_at_tail(&moves, (size_t)(moves_so_far + 1));
            }

        }

    }

    free_list(q.data);
    free_list(moves);
    return(-1);
}
