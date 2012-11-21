generating
generatePluginKernels
	"self generatePluginKernels"
	| kernels params type arg |
	self kernelDefinitionsDo: [:kernel :argDefs |
		self in: #GeziraBindingsMTPlugin
			classified: 'generated'
			compile: (String streamContents: [:stream |
				stream nextPutAll: 'kernel', kernel, ': argOops size: argCount';
					crtab; nextPutAll: '"Automatically generated (see generatePluginKernels)"';
					crtab; nextPutAll: '| result' .
				kernels := OrderedCollection new.
				params := OrderedCollection new.
				argDefs do: [:argDef |
					type := argDef first.
					arg := argDef second.
					(type = 'Kernel' ifTrue: [kernels] ifFalse: [params])
						add: arg.
					stream space; nextPutAll: arg].
				stream nextPutAll: ' |';
					crtab; nextPutAll: 'self returnTypeC: ''void''.';
					crtab; nextPutAll: 'self var: #argOops type: ''sqInt*''.';
					crtab; nextPutAll: 'self var: #result type: ''nile_Process_t*''.'.
 				argDefs do: [:argDef |
					stream crtab; nextPutAll: 'self var: #', argDef second, ' type: ''';
						nextPutAll: (argDef first = 'Kernel'
							ifTrue: ['nile_Process_t*']
							ifFalse: ['float']);
						nextPutAll: '''.'].
				stream crtab; nextPutAll: 'argCount ~= '; print: params size;
					crtab: 2; nextPutAll: 'ifTrue: [^self fail: ''wrong argument count in ', kernel, '''].'.
				kernels reverseDo: [:k |
					stream crtab; nextPutAll: k, ' := self popKernel.'].
				params withIndexDo: [:p :i |
					stream crtab; nextPutAll: p, ' := interpreterProxy floatValueOf: (argOops at: ', (i-1) asString, ').'].
				argDefs ifNotEmpty: [
					stream crtab; nextPutAll: 'interpreterProxy failed ifTrue: [^self fail: ''wrong arguments to ', kernel, '''].'].
				stream crtab; nextPutAll: 'result := self cCode: ''gezira_', kernel, '(init'.
				argDefs do: [:argDef | stream nextPutAll: ', ', argDef second].
				stream nextPutAll: ')''.';
					crtab; nextPutAll: 'self pushKernel: result.'; cr
				])]