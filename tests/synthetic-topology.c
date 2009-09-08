/*
 * Copyright © 2009 CNRS, INRIA, Université Bordeaux 1
 * See COPYING in top-level directory.
 */

#include <topology.h>

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

/* check that object userdata is properly initialized */

int main(void)
{
  topo_topology_t topology;
  struct topo_topology_info info;
  int i,j, width;

  /* check a synthetic topology */
  topo_topology_init(&topology);
  topo_topology_set_synthetic(topology, "2 3 4 5 6");
  topo_topology_load(topology);

  /* internal checks */

  topo_topology_check(topology);

  /* local checks */
  topo_topology_get_info(topology, &info);
  assert(info.depth == 6);

  width = 1;
  for(i=0; i<6; i++) {
    /* check arities */
    assert(topo_get_depth_nbobjs(topology, i) == width);
    for(j=0; j<width; j++) {
      topo_obj_t obj = topo_get_obj_by_depth(topology, i, j);
      assert(obj);
      assert(obj->arity == (i<5 ? i+2 : 0));
    }
    width *= i+2;
  }

  topo_topology_destroy(topology);

  return 0;
}
