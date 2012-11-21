generating
generatePluginDispatch
	"self generatePluginDispatch"
	| kernels |
	kernels := self extraKernels asOrderedCollection.
	self kernelDefinitionsDo:
		[:kernel :argDefs | kernels add: kernel].
	self in: #GeziraBindingsMTPlugin
		classified: 'generated'
		compile: (String streamContents: [:stream |
			stream
				nextPutAll: 'dispatchKernel: kernelName size: kernelNameSize arguments: argOops size: argCount';
				crtab; nextPutAll: '"Automatically generated (see generatePluginDispatch)"';
				crtab; nextPutAll: 'self returnTypeC: ''void''.';
				crtab; nextPutAll: 'self var: #argOops type: ''sqInt*''.';
				crtab; nextPutAll: 'self var: #kernelName type: ''char*''.'.
			kernels do: [:k |
				stream crtab; nextPutAll: '(self string: ''', k, ''' equals: kernelName len: kernelNameSize)';
					crtab: 2; nextPutAll: 'ifTrue: [^self kernel', k, ': argOops size: argCount].'].
			stream crtab; nextPutAll: 'self fail: ''Unknown kernel'''
		])