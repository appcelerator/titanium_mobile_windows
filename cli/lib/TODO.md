= TODO =
- Filter down list of includes in cpp files and WindowsNativeModuleLoader.cpp
	- We have the type dependency tree, we can likely eliminate many includes knowing that Type X includes Type Y, which includes Type Z, etc.
	
== Improvements to Metadata ==
- Consistently use "class Name.Of.Class" or "Name.Of.Class" for types. Probably the former.
- Mark API support for each type. There are types documented that work on windows Phone 10 tehcnical preview, but not 8 or 8.1.
- Pare down the amount of data to just what we need? (Doesn't matter much if just used to geenrate stubs and isn't getting embedded in app or shipped in distribution)
- Fix up naming of complex/templated types?