add_qtc_plugin(QmlDesigner
  DEPENDS
    qmljs LanguageUtils QmlEditorWidgets
    Qt5::QuickWidgets Qt5::CorePrivate
  DEFINES
    DESIGNER_CORE_LIBRARY
    IDE_LIBRARY_BASENAME=\"${IDE_LIBRARY_BASE_PATH}\"
  INCLUDES
    ${CMAKE_CURRENT_LIST_DIR}/designercore/include
  PLUGIN_DEPENDS
    Core ProjectExplorer QmlJSEditor QmakeProjectManager QmlProjectManager
    QtSupport TextEditor
  SOURCES
    designersettings.cpp designersettings.h
    designmodecontext.cpp designmodecontext.h
    designmodewidget.cpp designmodewidget.h
    documentmanager.cpp documentmanager.h
    documentwarningwidget.cpp documentwarningwidget.h
    openuiqmlfiledialog.cpp openuiqmlfiledialog.h openuiqmlfiledialog.ui
    qmldesignerconstants.h
    qmldesignericons.h
    qmldesignerplugin.cpp qmldesignerplugin.h
    settingspage.cpp settingspage.h settingspage.ui
    shortcutmanager.cpp shortcutmanager.h
    switchsplittabwidget.cpp switchsplittabwidget.h
  EXPLICIT_MOC
    components/propertyeditor/propertyeditorvalue.h
    qmldesignerextension/connectioneditor/connectionviewwidget.h
  SKIP_DEBUG_CMAKE_FILE_CHECK
)

set(QmlDesignerPluginInstallPrefix "${IDE_PLUGIN_PATH}/qmldesigner")
if (APPLE)
  set(QmlDesignerPluginInstallPrefix "${IDE_PLUGIN_PATH}/QmlDesigner")
endif()

add_qtc_plugin(componentsplugin
  DEPENDS Core QmlDesigner Utils Qt5::Qml
  DEFINES COMPONENTS_LIBRARY
  INCLUDES ${CMAKE_CURRENT_LIST_DIR}/designercore/include
  SOURCES
    componentsplugin/addtabdesigneraction.cpp componentsplugin/addtabdesigneraction.h
    componentsplugin/addtabtotabviewdialog.cpp componentsplugin/addtabtotabviewdialog.h
    componentsplugin/addtabtotabviewdialog.ui
    componentsplugin/componentsplugin.cpp componentsplugin/componentsplugin.h
    componentsplugin/componentsplugin.qrc
    componentsplugin/entertabdesigneraction.cpp componentsplugin/entertabdesigneraction.h
    componentsplugin/tabviewindexmodel.cpp componentsplugin/tabviewindexmodel.h
  PLUGIN_PATH ${QmlDesignerPluginInstallPrefix}
  SKIP_DEBUG_CMAKE_FILE_CHECK
)

add_qtc_plugin(qtquickplugin
  DEPENDS Core QmlDesigner Utils Qt5::Qml
  DEFINES QTQUICK_LIBRARY
  INCLUDES ${CMAKE_CURRENT_LIST_DIR}/designercore/include
  SOURCES
    qtquickplugin/qtquickplugin.cpp qtquickplugin/qtquickplugin.h
    qtquickplugin/qtquickplugin.qrc
  PLUGIN_PATH ${QmlDesignerPluginInstallPrefix}
  SKIP_DEBUG_CMAKE_FILE_CHECK
)

function(extend_qtc_plugin name directory)
  foreach(source ${ARGN})
    list(APPEND source_list ${directory}/${source})
  endforeach()
  target_sources(${name} PRIVATE ${source_list})
  target_include_directories(${name} PUBLIC ${directory})
endfunction(extend_qtc_plugin)

extend_qtc_plugin(QmlDesigner ../../../share/qtcreator/qml/qmlpuppet/container
  addimportcontainer.cpp addimportcontainer.h
  idcontainer.cpp idcontainer.h
  imagecontainer.cpp imagecontainer.h
  informationcontainer.cpp informationcontainer.h
  instancecontainer.cpp instancecontainer.h
  mockuptypecontainer.cpp mockuptypecontainer.h
  propertyabstractcontainer.cpp propertyabstractcontainer.h
  propertybindingcontainer.cpp propertybindingcontainer.h
  propertyvaluecontainer.cpp propertyvaluecontainer.h
  reparentcontainer.cpp reparentcontainer.h
  sharedmemory.h
)

if (UNIX)
  extend_qtc_plugin(QmlDesigner ../../../share/qtcreator/qml/qmlpuppet/container
    sharedmemory_unix.cpp
  )
  if (NOT APPLE)
    target_link_libraries(QmlDesigner PRIVATE rt)
  endif()
else()
  extend_qtc_plugin(QmlDesigner ../../../share/qtcreator/qml/qmlpuppet/container
    sharedmemory_qt.cpp
  )
endif()

extend_qtc_plugin(QmlDesigner ../../../share/qtcreator/qml/qmlpuppet/commands
  changeauxiliarycommand.cpp changeauxiliarycommand.h
  changebindingscommand.cpp changebindingscommand.h
  changefileurlcommand.cpp changefileurlcommand.h
  changeidscommand.cpp changeidscommand.h
  changenodesourcecommand.cpp changenodesourcecommand.h
  changestatecommand.cpp changestatecommand.h
  changevaluescommand.cpp changevaluescommand.h
  childrenchangedcommand.cpp childrenchangedcommand.h
  clearscenecommand.cpp clearscenecommand.h
  completecomponentcommand.cpp completecomponentcommand.h
  componentcompletedcommand.cpp componentcompletedcommand.h
  createinstancescommand.cpp createinstancescommand.h
  createscenecommand.cpp createscenecommand.h
  debugoutputcommand.cpp debugoutputcommand.h
  endpuppetcommand.cpp endpuppetcommand.h
  informationchangedcommand.cpp informationchangedcommand.h
  pixmapchangedcommand.cpp pixmapchangedcommand.h
  puppetalivecommand.cpp puppetalivecommand.h
  removeinstancescommand.cpp removeinstancescommand.h
  removepropertiescommand.cpp removepropertiescommand.h
  removesharedmemorycommand.cpp removesharedmemorycommand.h
  reparentinstancescommand.cpp reparentinstancescommand.h
  statepreviewimagechangedcommand.cpp statepreviewimagechangedcommand.h
  synchronizecommand.cpp synchronizecommand.h
  tokencommand.cpp tokencommand.h
  valueschangedcommand.cpp valueschangedcommand.h
)

extend_qtc_plugin(QmlDesigner ../../../share/qtcreator/qml/qmlpuppet/interfaces
  nodeinstanceserverinterface.cpp
  commondefines.h
  nodeinstanceclientinterface.h
  nodeinstanceglobal.h
  nodeinstanceserverinterface.h
)

extend_qtc_plugin(QmlDesigner ../../../share/qtcreator/qml/qmlpuppet/types
  enumeration.cpp enumeration.h
)

extend_qtc_plugin(QmlDesigner components/componentcore
  abstractaction.cpp abstractaction.h
  abstractactiongroup.cpp abstractactiongroup.h
  actioninterface.h
  addimagesdialog.cpp addimagesdialog.h
  addsignalhandlerdialog.cpp addsignalhandlerdialog.h addsignalhandlerdialog.ui
  changestyleaction.cpp changestyleaction.h
  componentcore.qrc
  componentcore_constants.h
  crumblebar.cpp crumblebar.h
  designeractionmanager.cpp designeractionmanager.h
  designeractionmanagerview.cpp designeractionmanagerview.h
  findimplementation.cpp findimplementation.h
  layoutingridlayout.cpp layoutingridlayout.h
  modelnodecontextmenu.cpp modelnodecontextmenu.h
  modelnodecontextmenu_helper.cpp modelnodecontextmenu_helper.h
  modelnodeoperations.cpp modelnodeoperations.h
  qmldesignericonprovider.cpp qmldesignericonprovider.h
  selectioncontext.cpp selectioncontext.h
  theme.cpp theme.h
  zoomaction.cpp zoomaction.h
)

extend_qtc_plugin(QmlDesigner components/debugview
  debugview.cpp debugview.h
  debugviewwidget.cpp debugviewwidget.h debugviewwidget.ui
)

extend_qtc_plugin(QmlDesigner components/formeditor
  abstractcustomtool.cpp abstractcustomtool.h
  abstractformeditortool.cpp abstractformeditortool.h
  anchorindicator.cpp anchorindicator.h
  anchorindicatorgraphicsitem.cpp anchorindicatorgraphicsitem.h
  backgroundaction.cpp backgroundaction.h
  bindingindicator.cpp bindingindicator.h
  bindingindicatorgraphicsitem.cpp bindingindicatorgraphicsitem.h
  contentnoteditableindicator.cpp contentnoteditableindicator.h
  controlelement.cpp controlelement.h
  dragtool.cpp dragtool.h
  formeditor.qrc
  formeditorgraphicsview.cpp formeditorgraphicsview.h
  formeditoritem.cpp formeditoritem.h
  formeditorscene.cpp formeditorscene.h
  formeditorsubwindow.h
  formeditortoolbutton.cpp formeditortoolbutton.h
  formeditorview.cpp formeditorview.h
  formeditorwidget.cpp formeditorwidget.h
  itemutilfunctions.cpp itemutilfunctions.h
  layeritem.cpp layeritem.h
  lineeditaction.cpp lineeditaction.h
  movemanipulator.cpp movemanipulator.h
  movetool.cpp movetool.h
  numberseriesaction.cpp numberseriesaction.h
  onedimensionalcluster.cpp onedimensionalcluster.h
  resizecontroller.cpp resizecontroller.h
  resizehandleitem.cpp resizehandleitem.h
  resizeindicator.cpp resizeindicator.h
  resizemanipulator.cpp resizemanipulator.h
  resizetool.cpp resizetool.h
  rubberbandselectionmanipulator.cpp rubberbandselectionmanipulator.h
  scaleitem.cpp scaleitem.h
  scalemanipulator.cpp scalemanipulator.h
  selectionindicator.cpp selectionindicator.h
  selectionrectangle.cpp selectionrectangle.h
  selectiontool.cpp selectiontool.h
  singleselectionmanipulator.cpp singleselectionmanipulator.h
  snapper.cpp snapper.h
  snappinglinecreator.cpp snappinglinecreator.h
  toolbox.cpp toolbox.h
)

extend_qtc_plugin(QmlDesigner components/importmanager
  importlabel.cpp importlabel.h
  importmanager.qrc
  importmanagercombobox.cpp importmanagercombobox.h
  importmanagerview.cpp importmanagerview.h
  importswidget.cpp importswidget.h
)

extend_qtc_plugin(QmlDesigner components/integration
  componentaction.cpp componentaction.h
  componentview.cpp componentview.h
  designdocument.cpp designdocument.h
  designdocumentview.cpp designdocumentview.h
  stackedutilitypanelcontroller.cpp stackedutilitypanelcontroller.h
  utilitypanelcontroller.cpp utilitypanelcontroller.h
)

extend_qtc_plugin(QmlDesigner components/itemlibrary
  customfilesystemmodel.cpp customfilesystemmodel.h
  itemlibrary.qrc
  itemlibraryimageprovider.cpp itemlibraryimageprovider.h
  itemlibraryitem.cpp itemlibraryitem.h
  itemlibrarymodel.cpp itemlibrarymodel.h
  itemlibraryresourceview.cpp itemlibraryresourceview.h
  itemlibrarysection.cpp itemlibrarysection.h
  itemlibrarysectionmodel.cpp itemlibrarysectionmodel.h
  itemlibraryview.cpp itemlibraryview.h
  itemlibrarywidget.cpp itemlibrarywidget.h
)

extend_qtc_plugin(QmlDesigner components/navigator
  iconcheckboxitemdelegate.cpp iconcheckboxitemdelegate.h
  nameitemdelegate.cpp nameitemdelegate.h
  navigator.qrc
  navigatormodelinterface.h
  navigatortreemodel.cpp navigatortreemodel.h
  navigatortreeview.cpp navigatortreeview.h
  navigatorview.cpp navigatorview.h
  navigatorwidget.cpp navigatorwidget.h
)

extend_qtc_plugin(QmlDesigner components/propertyeditor
  designerpropertymap.cpp designerpropertymap.h
  fileresourcesmodel.cpp fileresourcesmodel.h
  gradientmodel.cpp gradientmodel.h
  gradientpresetcustomlistmodel.cpp gradientpresetcustomlistmodel.h
  gradientpresetdefaultlistmodel.cpp gradientpresetdefaultlistmodel.h
  gradientpresetitem.cpp gradientpresetitem.h
  gradientpresetlistmodel.cpp gradientpresetlistmodel.h
  propertyeditorcontextobject.cpp propertyeditorcontextobject.h
  propertyeditorqmlbackend.cpp propertyeditorqmlbackend.h
  propertyeditortransaction.cpp propertyeditortransaction.h
  propertyeditorvalue.cpp propertyeditorvalue.h
  propertyeditorview.cpp propertyeditorview.h
  propertyeditorwidget.cpp propertyeditorwidget.h
  qmlanchorbindingproxy.cpp qmlanchorbindingproxy.h
  qmlmodelnodeproxy.cpp qmlmodelnodeproxy.h
  quick2propertyeditorview.cpp quick2propertyeditorview.h
)

extend_qtc_plugin(QmlDesigner components
  resources/resources.qrc
)

extend_qtc_plugin(QmlDesigner components/stateseditor
  stateseditorimageprovider.cpp stateseditorimageprovider.h
  stateseditormodel.cpp stateseditormodel.h
  stateseditorview.cpp stateseditorview.h
  stateseditorwidget.cpp stateseditorwidget.h
)

extend_qtc_plugin(QmlDesigner components/texteditor
  texteditorstatusbar.cpp texteditorstatusbar.h
  texteditorview.cpp texteditorview.h
  texteditorwidget.cpp texteditorwidget.h
)

extend_qtc_plugin(QmlDesigner designercore
  exceptions/exception.cpp
  exceptions/invalidargumentexception.cpp
  exceptions/invalididexception.cpp
  exceptions/invalidmetainfoexception.cpp
  exceptions/invalidmodelnodeexception.cpp
  exceptions/invalidmodelstateexception.cpp
  exceptions/invalidpropertyexception.cpp
  exceptions/invalidqmlsourceexception.cpp
  exceptions/invalidreparentingexception.cpp
  exceptions/invalidslideindexexception.cpp
  exceptions/notimplementedexception.cpp
  exceptions/removebasestateexception.cpp
  exceptions/rewritingexception.cpp

  filemanager/addarraymembervisitor.cpp filemanager/addarraymembervisitor.h
  filemanager/addobjectvisitor.cpp filemanager/addobjectvisitor.h
  filemanager/addpropertyvisitor.cpp filemanager/addpropertyvisitor.h
  filemanager/astobjecttextextractor.cpp filemanager/astobjecttextextractor.h
  filemanager/changeimportsvisitor.cpp filemanager/changeimportsvisitor.h
  filemanager/changeobjecttypevisitor.cpp filemanager/changeobjecttypevisitor.h
  filemanager/changepropertyvisitor.cpp filemanager/changepropertyvisitor.h
  filemanager/firstdefinitionfinder.cpp filemanager/firstdefinitionfinder.h
  filemanager/moveobjectbeforeobjectvisitor.cpp filemanager/moveobjectbeforeobjectvisitor.h
  filemanager/moveobjectvisitor.cpp filemanager/moveobjectvisitor.h
  filemanager/objectlengthcalculator.cpp filemanager/objectlengthcalculator.h
  filemanager/qmlrefactoring.cpp filemanager/qmlrefactoring.h
  filemanager/qmlrewriter.cpp filemanager/qmlrewriter.h
  filemanager/removepropertyvisitor.cpp filemanager/removepropertyvisitor.h
  filemanager/removeuiobjectmembervisitor.cpp filemanager/removeuiobjectmembervisitor.h

  include/abstractproperty.h
  include/abstractview.h
  include/anchorline.h
  include/basetexteditmodifier.h
  include/bindingproperty.h
  include/bytearraymodifier.h
  include/componenttextmodifier.h
  include/customnotifications.h
  include/documentmessage.h
  include/exception.h
  include/forwardview.h
  include/import.h
  include/invalidargumentexception.h
  include/invalididexception.h
  include/invalidmetainfoexception.h
  include/invalidmodelnodeexception.h
  include/invalidmodelstateexception.h
  include/invalidpropertyexception.h
  include/invalidqmlsourceexception.h
  include/invalidreparentingexception.h
  include/invalidslideindexexception.h
  include/itemlibraryinfo.h
  include/iwidgetplugin.h
  include/mathutils.h
  include/metainfo.h
  include/metainforeader.h
  include/model.h
  include/modelmerger.h
  include/modelnode.h
  include/modelnodepositionstorage.h
  include/modificationgroupexception.h
  include/modificationgrouptoken.h
  include/nodeabstractproperty.h
  include/nodeanchors.h
  include/nodehints.h
  include/nodeinstance.h
  include/nodeinstanceview.h
  include/nodelistproperty.h
  include/nodemetainfo.h
  include/nodeproperty.h
  include/notimplementedexception.h
  include/objectpropertybinding.h
  include/plaintexteditmodifier.h
  include/propertybinding.h
  include/propertycontainer.h
  include/propertynode.h
  include/propertyparser.h
  include/qmlanchors.h
  include/qmlchangeset.h
  include/qmldesignercorelib_global.h
  include/qmlitemnode.h
  include/qmlmodelnodefacade.h
  include/qmlobjectnode.h
  include/qmlstate.h
  include/qmltimeline.h
  include/qmltimelinekeyframegroup.h
  include/removebasestateexception.h
  include/rewriterview.h
  include/rewritingexception.h
  include/signalhandlerproperty.h
  include/subcomponentmanager.h
  include/textmodifier.h
  include/variantproperty.h
  include/viewmanager.h
)

extend_qtc_plugin(QmlDesigner designercore/instances
  nodeinstance.cpp
  nodeinstanceserverproxy.cpp nodeinstanceserverproxy.h
  nodeinstanceview.cpp
  puppetbuildprogressdialog.cpp puppetbuildprogressdialog.h puppetbuildprogressdialog.ui
  puppetcreator.cpp puppetcreator.h
  puppetdialog.cpp puppetdialog.h puppetdialog.ui
)

extend_qtc_plugin(QmlDesigner designercore
  metainfo/itemlibraryinfo.cpp
  metainfo/metainfo.cpp
  metainfo/metainforeader.cpp
  metainfo/nodehints.cpp
  metainfo/nodemetainfo.cpp
  metainfo/subcomponentmanager.cpp

  model/abstractproperty.cpp
  model/abstractview.cpp
  model/anchorline.cpp
  model/basetexteditmodifier.cpp
  model/bindingproperty.cpp
  model/componenttextmodifier.cpp
  model/documentmessage.cpp
  model/import.cpp
  model/internalbindingproperty.cpp model/internalbindingproperty.h
  model/internalnode.cpp model/internalnode_p.h
  model/internalnodeabstractproperty.cpp model/internalnodeabstractproperty.h
  model/internalnodelistproperty.cpp model/internalnodelistproperty.h
  model/internalnodeproperty.cpp model/internalnodeproperty.h
  model/internalproperty.cpp model/internalproperty.h
  model/internalsignalhandlerproperty.cpp model/internalsignalhandlerproperty.h
  model/internalvariantproperty.cpp model/internalvariantproperty.h
  model/model.cpp model/model_p.h
  model/modelmerger.cpp
  model/modelnode.cpp
  model/modelnodepositionrecalculator.cpp model/modelnodepositionrecalculator.h
  model/modelnodepositionstorage.cpp
  model/modeltotextmerger.cpp model/modeltotextmerger.h
  model/nodeabstractproperty.cpp
  model/nodelistproperty.cpp
  model/nodeproperty.cpp
  model/plaintexteditmodifier.cpp
  model/propertycontainer.cpp
  model/propertynode.cpp
  model/propertyparser.cpp
  model/qmlanchors.cpp
  model/qmlchangeset.cpp
  model/qmlitemnode.cpp
  model/qmlmodelnodefacade.cpp
  model/qmlobjectnode.cpp
  model/qmlstate.cpp
  model/qmltextgenerator.cpp model/qmltextgenerator.h
  model/qmltimeline.cpp
  model/qmltimelinekeyframegroup.cpp
  model/rewriteaction.cpp model/rewriteaction.h
  model/rewriteactioncompressor.cpp model/rewriteactioncompressor.h
  model/rewriterview.cpp
  model/signalhandlerproperty.cpp
  model/textmodifier.cpp
  model/texttomodelmerger.cpp model/texttomodelmerger.h
  model/variantproperty.cpp
  model/viewmanager.cpp

  pluginmanager/widgetpluginmanager.cpp pluginmanager/widgetpluginmanager.h
  pluginmanager/widgetpluginpath.cpp pluginmanager/widgetpluginpath.h
  rewritertransaction.cpp rewritertransaction.h
)

extend_qtc_plugin(QmlDesigner qmldesignerextension
  colortool/colortool.cpp colortool/colortool.h
)

extend_qtc_plugin(QmlDesigner qmldesignerextension/connectioneditor
  addnewbackenddialog.cpp addnewbackenddialog.h addnewbackenddialog.ui
  backendmodel.cpp backendmodel.h
  bindingmodel.cpp bindingmodel.h
  connectioneditor.qrc
  connectionmodel.cpp connectionmodel.h
  connectionview.cpp connectionview.h
  connectionviewwidget.cpp connectionviewwidget.h connectionviewwidget.ui
  delegates.cpp delegates.h
  dynamicpropertiesmodel.cpp dynamicpropertiesmodel.h
)

extend_qtc_plugin(QmlDesigner qmldesignerextension
  pathtool/controlpoint.cpp pathtool/controlpoint.h
  pathtool/cubicsegment.cpp pathtool/cubicsegment.h
  pathtool/pathitem.cpp pathtool/pathitem.h
  pathtool/pathselectionmanipulator.cpp pathtool/pathselectionmanipulator.h
  pathtool/pathtool.cpp pathtool/pathtool.h
  pathtool/pathtoolview.cpp pathtool/pathtoolview.h

  qmldesignerextensionconstants.h
  qmldesignerextension_global.h

  sourcetool/sourcetool.cpp sourcetool/sourcetool.h

  texttool/textedititem.cpp texttool/textedititem.h
  texttool/textedititemwidget.cpp texttool/textedititemwidget.h
  texttool/texttool.cpp texttool/texttool.h
)

extend_qtc_plugin(QmlDesigner qmldesignerextension/timelineeditor
  canvas.cpp canvas.h
  canvasstyledialog.cpp canvasstyledialog.h
  easingcurve.cpp easingcurve.h
  easingcurvedialog.cpp easingcurvedialog.h
  preseteditor.cpp preseteditor.h
  setframevaluedialog.cpp setframevaluedialog.h setframevaluedialog.ui
  splineeditor.cpp splineeditor.h
  timeline.qrc
  timelineabstracttool.cpp timelineabstracttool.h
  timelineactions.cpp timelineactions.h
  timelineanimationform.cpp timelineanimationform.h timelineanimationform.ui
  timelineconstants.h
  timelinecontext.cpp timelinecontext.h
  timelinecontrols.cpp timelinecontrols.h
  timelineform.cpp timelineform.h timelineform.ui
  timelinegraphicslayout.cpp timelinegraphicslayout.h
  timelinegraphicsscene.cpp timelinegraphicsscene.h
  timelineicons.h
  timelineitem.cpp timelineitem.h
  timelinemovableabstractitem.cpp timelinemovableabstractitem.h
  timelinemovetool.cpp timelinemovetool.h
  timelineplaceholder.cpp timelineplaceholder.h
  timelinepropertyitem.cpp timelinepropertyitem.h
  timelinesectionitem.cpp timelinesectionitem.h
  timelineselectiontool.cpp timelineselectiontool.h
  timelinesettingsdialog.cpp
  timelinesettingsdialog.h timelinesettingsdialog.ui
  timelinesettingsmodel.cpp timelinesettingsmodel.h
  timelinetoolbar.cpp timelinetoolbar.h
  timelinetoolbutton.cpp timelinetoolbutton.h
  timelinetooldelegate.cpp timelinetooldelegate.h
  timelineutils.cpp timelineutils.h
  timelineview.cpp timelineview.h
  timelinewidget.cpp timelinewidget.h
)

# Do the file comparison at the end, due to all the extend_qtc_plugin calls
if (WITH_DEBUG_CMAKE)
  foreach(plugin QmlDesigner componentsplugin qtquickplugin)
    unset(plugin_sources)
    get_target_property(plugin_sources ${plugin} SOURCES)
    list(APPEND QmlDesignerSources ${plugin_sources})
  endforeach()
  compare_sources_with_existing_disk_files(QmlDesigner "${QmlDesignerSources}")
endif()
