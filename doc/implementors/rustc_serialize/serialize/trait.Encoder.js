(function() {var implementors = {};
implementors["image"] = [];implementors["sdl2_window"] = [];implementors["glutin_window"] = [];implementors["piston_window"] = [];

            if (window.register_implementors) {
                window.register_implementors(implementors);
            } else {
                window.pending_implementors = implementors;
            }
        
})()
