lib_LTLIBRARIES = libneXtaw.la

libneXtaw_la_SOURCES = \
	AllWidgets.c AsciiSink.c AsciiSrc.c AsciiText.c Box.c \
	Clock.c Command.c Dialog.c Form.c Grip.c Label.c Layout.c \
	List.c MenuButton.c Misc.c MultiSink.c MultiSrc.c Paned.c \
	Panner.c Porthole.c Repeater.c Scrollbar.c Simple.c SimpleMenu.c \
	Sme.c SmeBSB.c SmeLine.c SmeThreeD.c StripChart.c Text.c \
	TextAction.c TextPop.c TextSink.c TextSrc.c TextTr.c TextTrOld.c \
	ThreeD.c \
	Toggle.c Traversal.c \
	Tree.c Vendor.c Viewport.c XawI18n.c XawIm.c XawInit.c \
	sharedlib.c laygram.c laylex.c

neXtawincludedir=$(includedir)/X11/neXtaw
neXtawinclude_HEADERS = \
	AllWidgets.h AsciiSink.h AsciiSinkP.h AsciiSrc.h AsciiSrcP.h \
	AsciiText.h AsciiTextP.h Box.h BoxP.h Cardinals.h Clock.h ClockP.h \
	Command.h CommandP.h Dialog.h DialogP.h Form.h FormP.h \
	Grip.h GripP.h Label.h LabelP.h Layout.h LayoutP.h List.h ListP.h \
	MenuButtoP.h MenuButton.h Misc.h MultiSink.h \
	MultiSinkP.h MultiSrc.h MultiSrcP.h Paned.h PanedP.h \
	Panner.h PannerP.h Porthole.h PortholeP.h Repeater.h RepeaterP.h \
	Reports.h Scrollbar.h ScrollbarP.h Simple.h \
	SimpleMenP.h SimpleMenu.h SimpleP.h Sme.h SmeBSB.h SmeBSBP.h \
	SmeLine.h SmeLineP.h SmeP.h SmeThreeD.h SmeThreeDP.h \
	StripCharP.h StripChart.h Text.h TextP.h TextSink.h TextSinkP.h \
	TextSrc.h TextSrcP.h ThreeD.h ThreeDP.h Toggle.h ToggleP.h \
	Traversal.h TraversalP.h \
	Tree.h TreeP.h VendorEP.h Viewport.h ViewportP.h \
	XawAlloc.h XawI18n.h XawImP.h XawInit.h XawVersion.h laygram.h

libneXtaw_la_LDFLAGS = -version-info 15:1:15

INCLUDES = -DUSEGRAY -DNO_MENU_LINES \
	-DNeedFunctionPrototypes -I$(top_srcdir)

EXTRA_DIST = Template.c Template.h TemplateP.h \
	laygram.y laylex.l

laygram.c : laygram.y
	$(YACC) -d laygram.y
	sed 's/yy/LayYY/g' y.tab.c > laygram.c
	sed 's/yy/LayYY/g' y.tab.h > laygram.h
	$(RM) y.tab.c y.tab.h

laylex.c : laylex.l
	$(LEX) laylex.l
	sed 's/yy/LayYY/g' lex.yy.c > laylex.c
	$(RM) lex.yy.c
