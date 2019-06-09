find_path(LibNL_INCLUDE_DIR netlink/netlink.h
    /usr/include
    /usr/include/libnl3
    /usr/local/include
    /usr/local/include/libnl3
)

find_library(LibNL_LIBRARY NAMES nl nl-3)
find_library(LibNL_GENL_LIBRARY NAMES nl-genl nl-genl-3)

if (LibNL_INCLUDE_DIR AND LibNL_LIBRARY)
    set(LibNL_FOUND TRUE)
endif (LibNL_INCLUDE_DIR AND LibNL_LIBRARY)

if (LibNL_FOUND)
    set(LibNL_LIBRARIES ${LibNL_LIBRARY} ${LibNL_GENL_LIBRARY})
endif(LibNL_FOUND)
