ADD_LIBRARY           (Util STATIC UtilString.cxx)

ADD_LIBRARY           (Log STATIC LogDefaults.cxx)

ADD_LIBRARY           (Net STATIC NetConnection.cxx NetServer.cxx)
TARGET_LINK_LIBRARIES (Net ${boost_LIBRARIES})

ADD_EXECUTABLE        (${CMAKE_PROJECT_NAME} Main.cxx)
TARGET_LINK_LIBRARIES (${CMAKE_PROJECT_NAME} Net)
