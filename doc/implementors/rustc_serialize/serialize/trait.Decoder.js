(function() {var implementors = {};
implementors["num"] = [];implementors["enum_primitive"] = [];implementors["image"] = [];implementors["glutin_window"] = [];implementors["opengl_graphics"] = [];

            if (window.register_implementors) {
                window.register_implementors(implementors);
            } else {
                window.pending_implementors = implementors;
            }
        
})()
