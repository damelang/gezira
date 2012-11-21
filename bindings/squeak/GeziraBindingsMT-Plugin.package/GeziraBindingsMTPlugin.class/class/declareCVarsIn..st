translation
declareCVarsIn: cg
	super declareCVarsIn: cg.

	cg addHeaderFile: '"gezira.h"'.
	cg addHeaderFile: '"gezira-image.h"'.
	cg addHeaderFile: '<unistd.h>'.

	cg var: #init type: #'nile_Process_t*'.
	cg var: #mem type: #'char*'.
	cg var: #stack declareC: #'nile_Process_t* stack[100]'.
	cg var: #stackP type: #int.
	cg var: #images declareC: #'gezira_Image_t images[100]'.
	cg var: #errorMsg type: #'char*'.

	cg var: #m23ResultX type: #double.
	cg var: #m23ResultY type: #double.
	cg var: #m23ArgX type: #double.
	cg var: #m23ArgY type: #double