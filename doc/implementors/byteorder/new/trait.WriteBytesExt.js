(function() {var implementors = {};
implementors["wayland_window"] = [];implementors["winit"] = [];implementors["glutin"] = [];implementors["glutin_window"] = [];implementors["image"] = [];implementors["opengl_graphics"] = [];implementors["opengl_graphics"] = [];

            if (window.register_implementors) {
                window.register_implementors(implementors);
            } else {
                window.pending_implementors = implementors;
            }
        
})()
