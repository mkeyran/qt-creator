if (WITH_TESTS)
  set(TEST_COMPONENT QmakeProjectManager QtSupport)
endif()

add_qtc_plugin(AutoTest
  PLUGIN_DEPENDS Core CppTools Debugger ProjectExplorer QmlJSTools TextEditor ${TEST_COMPONENT}
  SOURCES
    autotest.qrc
    autotest_global.h
    autotestconstants.h
    autotesticons.h
    autotestplugin.cpp autotestplugin.h
    autotestunittests.qrc
    gtest/gtest_utils.cpp gtest/gtest_utils.h
    gtest/gtestconfiguration.cpp gtest/gtestconfiguration.h
    gtest/gtestconstants.h
    gtest/gtestframework.cpp gtest/gtestframework.h
    gtest/gtestoutputreader.cpp gtest/gtestoutputreader.h
    gtest/gtestparser.cpp gtest/gtestparser.h
    gtest/gtestresult.cpp gtest/gtestresult.h
    gtest/gtestsettings.cpp gtest/gtestsettings.h
    gtest/gtestsettingspage.cpp gtest/gtestsettingspage.h gtest/gtestsettingspage.ui
    gtest/gtesttreeitem.cpp gtest/gtesttreeitem.h
    gtest/gtestvisitors.cpp gtest/gtestvisitors.h
    iframeworksettings.h
    itestframework.h
    itestparser.cpp itestparser.h
    itestsettingspage.h
    qtest/qttest_utils.cpp qtest/qttest_utils.h
    qtest/qttestconfiguration.cpp qtest/qttestconfiguration.h
    qtest/qttestconstants.h
    qtest/qttestframework.cpp qtest/qttestframework.h
    qtest/qttestoutputreader.cpp qtest/qttestoutputreader.h
    qtest/qttestparser.cpp qtest/qttestparser.h
    qtest/qttestresult.cpp qtest/qttestresult.h
    qtest/qttestsettings.cpp qtest/qttestsettings.h
    qtest/qttestsettingspage.cpp qtest/qttestsettingspage.h qtest/qttestsettingspage.ui
    qtest/qttesttreeitem.cpp qtest/qttesttreeitem.h
    qtest/qttestvisitors.cpp qtest/qttestvisitors.h
    quick/quicktest_utils.cpp quick/quicktest_utils.h
    quick/quicktestconfiguration.cpp quick/quicktestconfiguration.h
    quick/quicktestframework.cpp quick/quicktestframework.h
    quick/quicktestparser.cpp quick/quicktestparser.h
    quick/quicktesttreeitem.cpp quick/quicktesttreeitem.h
    quick/quicktestvisitors.cpp quick/quicktestvisitors.h
    testcodeparser.cpp testcodeparser.h
    testconfiguration.cpp testconfiguration.h
    testeditormark.cpp testeditormark.h
    testframeworkmanager.cpp testframeworkmanager.h
    testnavigationwidget.cpp testnavigationwidget.h
    testoutputreader.cpp testoutputreader.h
    testresult.cpp testresult.h
    testresultdelegate.cpp testresultdelegate.h
    testresultmodel.cpp testresultmodel.h
    testresultspane.cpp testresultspane.h
    testrunconfiguration.h
    testrunner.cpp testrunner.h
    testsettings.cpp testsettings.h
    testsettingspage.cpp testsettingspage.h testsettingspage.ui
    testtreeitem.cpp testtreeitem.h
    testtreeitemdelegate.cpp testtreeitemdelegate.h
    testtreemodel.cpp testtreemodel.h
    testtreeview.cpp testtreeview.h
)

if (WITH_TESTS)
  target_sources(AutoTest PRIVATE
    autotestunittests.cpp autotestunittests.h
  )
endif()
