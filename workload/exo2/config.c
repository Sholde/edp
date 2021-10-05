#include <stdio.h>
#include <stdlib.h>

#include "config.h"

config_t *read_config_file(char *filename)
{
  // Check if filename is null
  if (!filename)
    {
      printf("Error: filename is null\n");
      exit(1);
    }

  // Open file
  FILE *f = fopen(filename, "r");

  // Check if is open
  if (!f)
    {
      printf("Error: can not open the file %s\n", filename);
      exit(1);
    }

  config_t *config = aligned_alloc(ALIGNED, sizeof(config_t));

  u64 tmp[10];

  // Number of request
  fscanf(f, "%llu\n", &(config->n));

  // Start time
  fscanf(f, "%s %llu %llu\n",
         config->start, &(tmp[0]), &(tmp[1]));
  config->t_0 = tmp[0];
  config->t = tmp[1];
  config->t_min = tmp[0];
  config->t_max = tmp[1];

  // Type
  fscanf(f, "%s %llu %llu\n",
         config->type, &(tmp[0]), &(tmp[1]));
  config->p = tmp[0];
  config->n_r = tmp[0];
  config->n_w = tmp[1];

  // Adress
  fscanf(f, "%s %llu %llu %llu\n",
         config->address, &(tmp[0]), &(tmp[1]), &(tmp[2]));
  config->a = tmp[0];
  config->s = tmp[1];
  config->a_min = tmp[0];
  config->a_max = tmp[1];
  config->h = tmp[0];
  config->c = tmp[1];
  config->p_h = tmp[2];

  // Size
  fscanf(f, "%s %llu %llu\n",
         config->size, &(tmp[0]), &(tmp[1]));
  config->s_size = tmp[0];
  config->s_min = tmp[0];
  config->s_max = tmp[1];
  config->s_mean = tmp[0];
  config->s_var = tmp[1];

  // Close file
  fclose(f);

  return config;
}

void free_config(config_t *config)
{
  free(config);
}
