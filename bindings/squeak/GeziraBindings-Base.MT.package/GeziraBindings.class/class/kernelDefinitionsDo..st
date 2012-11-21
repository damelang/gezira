definitions
kernelDefinitionsDo: aBlock
	"self kernelDefinitionsDo: [:kernel :args | Transcript cr; show: kernel, ': ', args asString; cr]"
	| s kernel arguments |
	s := self kernelDefinitions readStream.
	[s atEnd] whileFalse: [
		kernel := (s upTo: $() withBlanksTrimmed.
		arguments := ((s upTo: $)) findTokens: ',') asArray
			collect: [:arg | 
				{(arg copyUpToLast: Character space) withBlanksTrimmed.
				((arg copyAfterLast: Character space) copyReplaceAll: '_' with: ' ')
					withFirstCharacterDownshifted toCamelCase}].
		aBlock value: kernel value: arguments].