# Gezira bindings for Squeak

The bindings for Squeak come in two parts:

1. A plugin that links to the C runtime: Load "GeziraBindingsMT-Plugin" package and use VMMaker to generate the plugin sources, then compile.

2. Image-side support classes: Load "GeziraBindings-Base.MT" package and try the class-side examples in `GeziraBindings` and `GeziraCanvas`, which use the compiled plugin.

## Installing

The source packages can be installed using [FileTree for Monticello](https://github.com/dalehenrich/filetree/blob/master/doc/SqueakInstall.md):

    (Installer ss3 project: 'FileTree')
        install: 'MonticelloFileTree-Core.squeak43';
	    install: 'MonticelloFileTree-FileDirectory-Utilities.squeak43'

In Monticello, add a new "filetree://" repository, selecting this directory (`bindings/squeak`). Then load the packages from that repository as usual.
