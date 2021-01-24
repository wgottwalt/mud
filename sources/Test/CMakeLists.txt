ADD_EXECUTABLE        (TestLogReceiver LogReceiver.cxx)
TARGET_LINK_LIBRARIES (TestLogReceiver Log Support)

ADD_EXECUTABLE        (TestTimeSupport Time.cxx)
TARGET_LINK_LIBRARIES (TestTimeSupport Support)
