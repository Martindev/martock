(function() {var implementors = {};
implementors["rand"] = [];implementors["sdl2"] = [];implementors["tempfile"] = [];implementors["wayland_window"] = [];implementors["image"] = [];implementors["winit"] = [];implementors["glutin"] = [];implementors["sdl2_window"] = [];implementors["glutin_window"] = [];implementors["piston_window"] = [];

            if (window.register_implementors) {
                window.register_implementors(implementors);
            } else {
                window.pending_implementors = implementors;
            }
        
})()
