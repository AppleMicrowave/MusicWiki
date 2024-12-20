cmake_minimum_required(VERSION 3.16)

project(MusicWiki VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Quick)
find_package(Qt6 REQUIRED COMPONENTS Widgets)
find_package(Qt6 REQUIRED COMPONENTS Sql)

qt_standard_project_setup(REQUIRES 6.5)

qt_add_executable(appMusicWiki
    main.cpp
)

qt_add_qml_module(appMusicWiki
    URI MusicWiki
    VERSION 1.0
    QML_FILES
        Main.qml
        WelcomePage.qml
        SubListPage.qml
        ItemDetailsPage.qml
        SOURCES itemmanager.h itemmanager.cpp
        SOURCES dbmanager.h dbmanager.cpp
        SOURCES itemmodel.h itemmodel.cpp
        RESOURCES qml.qrc
        RESOURCES
        RESOURCES images/stratocaster.png
        RESOURCES images/yamaha_c40.png
        RESOURCES images/dw_performance_tom.png images/eastman_md315.png images/martin_d28.png images/meinl_cowbell.png images/pearl_export.png images/precision_bass.png images/prs_se_custom_24.png images/roland_td17kv.png images/stagg_edb.png images/stentor_student1.png images/stratocaster.png images/yamaha_c40.png images/yamaha_v3.png images/yamaha_va7.png images/zildjian_acustom.png
        RESOURCES images/akai_mpc_live_2.png images/akai_mpk249.png images/bach_stradivarius.png images/buffet_b12.png images/dw_performance_tom.png images/eastman_md315.png images/flight_diana.png images/hammond_skx.png images/hohner_erica.png images/kawai_k300.png images/korg_kronos_2.png images/ludwig_supraphonic.png images/martin_d28.png images/meinl_cowbell.png images/meinl_headliner.png images/meinl_tambourine.png images/pearl_export.png images/precision_bass.png images/prs_se_custom_24.png images/roland_fr8x.png images/roland_juno_ds61.png images/roland_td17kv.png images/schlagwerk_cp404.png images/stagg_edb.png images/steinway_d.png images/stentor_student1.png images/stratocaster.png images/tula_t1.png images/viscount_legend.png images/weltmeister_supita.png images/yamaha_c40.png images/yamaha_p125.png images/yamaha_stage_custom.png images/yamaha_v3.png images/yamaha_va7.png images/yamaha_yas280.png images/yamaha_yfl222.png images/yamaha_yob241.png images/yamaha_ysl354.png images/zildjian_acustom.png
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(appMusicWiki PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.appMusicWiki
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(appMusicWiki
    PRIVATE Qt6::Quick Qt6::Widgets Qt6::Sql
)

include(GNUInstallDirs)
install(TARGETS appMusicWiki
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
