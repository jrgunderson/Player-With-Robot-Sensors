FILE(REMOVE_RECURSE
  "example_interface.h"
  "example_xdr.h"
  "example_xdr.c"
  "example_functiontable.c"
  "CMakeFiles/example.dir/example_xdr.o"
  "CMakeFiles/example.dir/eginterf_client.o"
  "CMakeFiles/example.dir/example_functiontable.o"
  "libexample.pdb"
  "libexample.so"
)

# Per-language clean rules from dependency scanning.
FOREACH(lang C)
  INCLUDE(CMakeFiles/example.dir/cmake_clean_${lang}.cmake OPTIONAL)
ENDFOREACH(lang)
