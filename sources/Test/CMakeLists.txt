ADD_EXECUTABLE        (TestLogReceiver LogReceiver.cxx)
TARGET_LINK_LIBRARIES (TestLogReceiver Log Support)

ADD_EXECUTABLE        (TestStringList StringList.cxx)
TARGET_LINK_LIBRARIES (TestStringList Support)

ADD_EXECUTABLE        (TestThreadPool ThreadPool.cxx)
TARGET_LINK_LIBRARIES (TestLogReceiver Support)

ADD_EXECUTABLE        (TestTimeSupport Time.cxx)
TARGET_LINK_LIBRARIES (TestLogReceiver Support)

ADD_EXECUTABLE        (TestTokenizer Tokenizer.cxx)
TARGET_LINK_LIBRARIES (TestTokenizer Session Support)
