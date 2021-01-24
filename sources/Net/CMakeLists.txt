ADD_LIBRARY           (Net STATIC Connection.cxx Server.cxx)
TARGET_LINK_LIBRARIES (Net ${boost_LIBRARIES})
