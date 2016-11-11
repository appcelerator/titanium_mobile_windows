using System;
using System.Collections.Generic;

namespace TitaniumWindows_Hyperloop
{
    public sealed class TypeHelper
    {
        private static Dictionary<string, string> KnownTypes = new Dictionary<string, string>()
            {
                { "System.Object",    typeof(System.Object).AssemblyQualifiedName },
                { "System.String",    typeof(System.String).AssemblyQualifiedName },
            };

        private static Dictionary<string, string> AssemblyQualifiedName = new Dictionary<string, string>()
            {
                { "Windows.System.MemoryManager", typeof(Windows.System.MemoryManager).AssemblyQualifiedName },
                { "System.Math", typeof(System.Math).AssemblyQualifiedName },
                { "Windows.UI.Xaml.Controls.Button", typeof(Windows.UI.Xaml.Controls.Button).AssemblyQualifiedName }
            };

        public static Type GetType(string className)
        {
            if (!KnownTypes.ContainsKey(className) && !AssemblyQualifiedName.ContainsKey(className))
            {
                throw new TypeLoadException("Unable to find AssemblyQualifiedName for " + className);
            }

            //
            // Extract assembly qualified name for Windows namespace. 
            //
            string assemblyQualifiedName;
            if (!KnownTypes.TryGetValue(className, out assemblyQualifiedName))
            {
                AssemblyQualifiedName.TryGetValue(className, out assemblyQualifiedName);
            }

            Type type = Type.GetType(assemblyQualifiedName);
            if (type == null)
            {
                throw new TypeLoadException("Unable to load " + className);
            }

            return type;
        }
    }
}
