#ifndef _CONFIG_H_
#define _CONFIG_H_

#define MAX_SIZE_BUFFER 256
#define ALIGNED 64

typedef unsigned long long u64;

typedef struct config_s
{
  // Number of data
  u64 n;

  // Start date variable
  char start[MAX_SIZE_BUFFER];
  u64 t_0;
  u64 t;
  u64 t_min;
  u64 t_max;

  // Type variable
  char type[MAX_SIZE_BUFFER];
  u64 p;
  u64 n_r;
  u64 n_w;

  // Address variable
  char address[MAX_SIZE_BUFFER];
  u64 a;
  u64 s;
  u64 a_min;
  u64 a_max;
  u64 h;
  u64 c;
  u64 p_h;

  // Size variable
  char size[MAX_SIZE_BUFFER];
  u64 s_size;
  u64 s_min;
  u64 s_max;
  u64 s_mean;
  u64 s_var;
} config_t;

config_t *read_config_file(char *filename);
void free_config(config_t *config);

#endif // _CONFIG_H_
