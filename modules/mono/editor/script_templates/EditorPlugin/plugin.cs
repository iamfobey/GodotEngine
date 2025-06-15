// meta-description: Basic plugin template

#if TOOLS
using _BINDINGS_NAMESPACE_;
using System;

[Tool]
public partial class _CLASS_ : _BASE_
{
    public override void _EnterTreeEditor()
    {
        // Initialization of the plugin goes here.
    }

    public override void _ExitTreeEditor()
    {
        // Clean-up of the plugin goes here.
    }
}
#endif
