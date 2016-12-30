(function() {var implementors = {};
implementors["float"] = [];implementors["sdl2_window"] = [];implementors["graphics"] = [];implementors["opengl_graphics"] = [];

            if (window.register_implementors) {
                window.register_implementors(implementors);
            } else {
                window.pending_implementors = implementors;
            }
        
})()
