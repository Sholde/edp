#include <stdio.h>
#include <stdlib.h>

#include "config.h"
#include "request.h"

int main(int argc, char **argv)
{
  if (argc != 3)
    {
      printf("Need 2 arguments:\n");
      printf("  1. config file\n");
      printf("  2. output file\n");
      return 1;
    }

  config_t *config = read_config_file(argv[1]);
  request_t *r = gen_request(config);

  print_request(argv[2], r);

  free_config(config);
  free_request(r);

  return 0;
}
