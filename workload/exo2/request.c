#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "config.h"
#include "request.h"

#include <time.h>

static void init_random()
{
  srand(time(NULL));
}

static u64 get_random()
{
  return rand();
}

// [0, n - 1]
u64 *gen_estampille(u64 n)
{
  u64 *e = aligned_alloc(ALIGNED, sizeof(u64) * n);

  for (u64 i = 0; i < n; i++)
    e[i] = i;

  return e;
}

// [t_0, t_0 + t, t_0 + 2t, ..., t_0 + (n - 1)t]
u64 *gen_start_seq(u64 n, u64 t_0, u64 t)
{
  u64 *start = aligned_alloc(ALIGNED, sizeof(u64) * n);

  for (u64 i = 0; i < n; i++)
    start[i] = t_0 + i * t;

  return start;
}

// [t_min, t_0 + random(t_min, t_max), t_1 + random(t_min, t_max), ...]
u64 *gen_start_uniform(u64 n, u64 t_min, u64 t_max)
{
  u64 *start = aligned_alloc(ALIGNED, sizeof(u64) * n);

  init_random();

  start[0] = t_min;

  for (u64 i = 1; i < n; i++)
    start[i] = start[i - 1] + get_random() % (t_max - t_min + 1) + t_min;

  return start;
}

// For type, I encoded read as 0 and write as 1
// Here p, the probability, need to be between [0, 100]
// Because I use unsigned long long which are 64 unsigned integer
u64 *gen_type_seq(u64 n, u64 p)
{
  // Check if probability is between [0, 100]
  if (p > 100)
    {
      printf("p need to be between [0, 100]\n");
      exit(2);
    }

  u64 *type = aligned_alloc(ALIGNED, sizeof(u64) * n);

  init_random();

  for (u64 i = 0; i < n; i++)
    {
      // draw a random number between [0, 100] to compare with probability p
      u64 is_write = get_random() % 101;

      if (is_write < p)
        type[i] = 1; // write
      else
        type[i] = 0; // read
    }

  return type;
}

// For type, I encoded read as 0 and write as 1
// n_r: number of read
// n_w: number of write
u64 *gen_type_uniform(u64 n, u64 n_r, u64 n_w)
{
  u64 *type = aligned_alloc(ALIGNED, sizeof(u64) * n);

  u64 r_w = 0;   // specify the current type
  u64 count = 0; // count the current type

  for (u64 i = 0; i < n; i++)
    {
      if (r_w == 0 && count == n_r) // done n_r read
        {
          r_w = 1;   // change to write
          count = 0; // reset counter
        }
      else if (r_w == 1 && count == n_w) // done n_w write
        {
          r_w = 0;   // change to read
          count = 0; // reset counter
        }

      type[i] = r_w;
      count++;
    }

  return type;
}

// [a, a + s, a + 2s, ..., a + (n - 1)s]
u64 *gen_addr_seq(u64 n, u64 a, u64 s)
{
  u64 *addr = aligned_alloc(ALIGNED, sizeof(u64) * n);

  for (u64 i = 0; i < n; i++)
    addr[i] = a + i * s;

  return addr;
}

// [random(a_min, a_max), ...]
u64 *gen_addr_uniform(u64 n, u64 a_min, u64 a_max)
{
  u64 *addr = aligned_alloc(ALIGNED, sizeof(u64) * n);

  init_random();

  for (u64 i = 0; i < n; i++)
    addr[i] = get_random() % (a_max - a_min + 1) + a_min;

  return addr;
}

// Here p_h is a probability and it need to be between [0, 100]
// Because I use unsigned long long which are 64 unsigned integer
u64 *gen_addr_random(u64 n, u64 h, u64 c, u64 p_h)
{
  // Check if p_h is between [0, 100]
  if (p_h > 100)
    {
      printf("p_h need to be between [0, 100]\n");
      exit(2);
    }

  u64 *addr = aligned_alloc(ALIGNED, sizeof(u64) * n);

  init_random();

  for (u64 i = 0; i < n; i++)
    {
      // draw a random number between [0, 100] to compare with probability p_h
      u64 p = get_random() % 101;

      if (p < p_h)
        addr[i] = get_random() % h;     // [0, h[
      else
        addr[i] = get_random() % c + h; // [h, h + c[
    }

  return addr;
}

// [s, s, .., s]
u64 *gen_size_seq(u64 n, u64 s)
{
  u64 *size = aligned_alloc(ALIGNED, sizeof(u64) * n);

  for (u64 i = 0; i < n; i++)
    size[i] = s;

  return size;
}

// [random(s_min, s_max), ...]
u64 *gen_size_uniform(u64 n, u64 s_min, u64 s_max)
{
  u64 *size = aligned_alloc(ALIGNED, sizeof(u64) * n);

  init_random();

  for (u64 i = 0; i < n; i++)
    size[i] = get_random() % (s_max - s_min + 1) + s_min;

  return size;
}

// To do
u64 *gen_size_normal(u64 n, u64 s_mean, u64 s_var)
{
  u64 *size = aligned_alloc(ALIGNED, sizeof(u64) * n);

  double mean = (double)s_mean;
  double var = (double)s_var;

  for (u64 i = 0; i < n; i++)
    size[i] = (exp(pow(i - mean, 2) / (2 * pow(var, 2)))
               * (var * sqrt((double)2 * PI)));

  return size;
}

request_t *gen_request(config_t *config)
{
  // Allocated memory
  request_t *r = aligned_alloc(ALIGNED, sizeof(request_t));

  // Check if request if allocated
  if (!r)
    exit(2);

  // Set the number of request
  r->n = config->n;

  // Generate estampille
  r->estampille = gen_estampille(config->n);

  // Generate start time
  if (strcmp(config->start, "seq") == 0)
    r->start = gen_start_seq(config->n, config->t_0, config->t);
  else if (strcmp(config->start, "uniform") == 0)
    r->start = gen_start_uniform(config->n, config->t_min, config->t_max);
  else
    printf("Error: start_time %s instead of {seq, uniform}\n", config->start), exit(3);

  // Generate type
  if (strcmp(config->type, "random") == 0)
    r->type = gen_type_seq(config->n, config->p);
  else if (strcmp(config->type, "stream") == 0)
    r->type = gen_type_uniform(config->n, config->n_r, config->n_w);
  else
    printf("Error: type %s instead of {random, stream}\n", config->type), exit(3);

  // Generate address
  if (strcmp(config->address, "seq") == 0)
    r->address = gen_addr_seq(config->n, config->a, config->s);
  else if (strcmp(config->address, "uniform") == 0)
    r->address = gen_addr_uniform(config->n, config->a_min, config->a_max);
  else if (strcmp(config->address, "random") == 0)
    r->address = gen_addr_random(config->n, config->h, config->c, config->p_h);
  else
    printf("Error: type %s instead of {seq, uniform, random}\n", config->address), exit(3);

  // Generate size
  if (strcmp(config->size, "seq") == 0)
    r->size = gen_size_seq(config->n, config->s_size);
  else if (strcmp(config->size, "uniform") == 0)
    r->size = gen_size_uniform(config->n, config->s_min, config->s_max);
  else if (strcmp(config->size, "normal") == 0)
    r->size = gen_size_normal(config->n, config->s_mean, config->s_var);
  else
    printf("Error: type %s instead of {seq, uniform, normal}\n", config->size), exit(3);

  return r;
}

void print_request(char *filename, request_t *r)
{
  // Check if filename is null
  if (!filename)
    {
      printf("Error: filename is null\n");
      exit(1);
    }

  // Open file
  FILE *f = fopen(filename, "w");

  // Check if is open
  if (!f)
    {
      printf("Error: can not open the file %s\n", filename);
      exit(1);
    }

  // Print request
  for (u64 i = 0; i < r->n; i++)
    {
      fprintf(f, "%lld %lld %lld %lld %lld\n",
              r->estampille[i],
              r->start[i],
              r->type[i],
              r->address[i],
              r->size[i]);
    }

  // Close file
  fclose(f);
}

void free_request(request_t *r)
{
  free(r->estampille);
  free(r->start);
  free(r->type);
  free(r->address);
  free(r->size);
}
