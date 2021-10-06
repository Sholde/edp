#include <stdio.h>
#include <stdlib.h>

#include "config.h"
#include "request.h"

int main(int argc, char **argv)
{
  // Check argument
  if (argc != 3)
    {
      printf("Need 2 arguments:\n");
      printf("  1. config file\n");
      printf("  2. output file\n");
      return 1;
    }

  // Init
  config_t *config = read_config_file(argv[1]);
  request_t *r = gen_request(config);

  // Print request
  print_request(argv[2], r);
  print_stats(r);

  // Release memory
  free_config(config);
  free_request(r);

  return 0;
}
