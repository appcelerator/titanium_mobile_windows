using System;
using System.Collections.Generic;

namespace TitaniumWindows_Hyperloop
{
    public delegate void HyperloopEventHandler(Event evt, object e);

    public sealed class Event
    {
        public event HyperloopEventHandler GotEvent;

        public object Target { get; set; }
        public string Name   { get; set; }

        public Event(string name, object target)
        {
            Target = target;
            Name = name;
        }

        public void HandleEvent(object sender, object e)
        {
            GotEvent?.Invoke(this, e);
        }
    }

    public sealed class EventHelper
    {
        public static Event add_Tapped_Windows_UI_Xaml_Controls_Button(object target)
        {
            Event evt = new Event("Tapped", target);
            ((Windows.UI.Xaml.Controls.Button)target).Tapped += evt.HandleEvent;
            return evt;
        }

        public static void remove_Tapped_Windows_UI_Xaml_Controls_Button(object evt, object target)
        {
            ((Windows.UI.Xaml.Controls.Button)target).Tapped -= ((Event)evt).HandleEvent;
        }
    }

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
