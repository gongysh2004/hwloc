/*
 * Copyright © 2009 CNRS, INRIA, Université Bordeaux 1
 * See COPYING in top-level directory.
 */

#include <hwloc.h>

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

/* check that object userdata is properly initialized */

static void check(hwloc_topology_t topology)
{
  struct hwloc_topology_info topoinfo;
  unsigned i,j;

  hwloc_topology_get_info(topology, &topoinfo);
  for(i=0; i<topoinfo.depth; i++) {
    for(j=0; j<hwloc_get_nbobjs_by_depth(topology, i); j++) {
      assert(hwloc_get_obj_by_depth(topology, i, j)->userdata == NULL);
    }
  }
}

int main(void)
{
  hwloc_topology_t topology;

  /* check the real topology */
  hwloc_topology_init(&topology);
  hwloc_topology_load(topology);
  check(topology);
  hwloc_topology_destroy(topology);

  /* check a synthetic topology */
  hwloc_topology_init(&topology);
  hwloc_topology_set_synthetic(topology, "6 5 4 3 2");
  hwloc_topology_load(topology);
  check(topology);
  hwloc_topology_destroy(topology);

  return 0;
}
