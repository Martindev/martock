(function() {var implementors = {};
implementors["sdl2_window"] = ["impl <a class='trait' href='window/trait.OpenGLWindow.html' title='window::OpenGLWindow'>OpenGLWindow</a> for <a class='struct' href='sdl2_window/struct.Sdl2Window.html' title='sdl2_window::Sdl2Window'>Sdl2Window</a>",];implementors["glutin_window"] = ["impl <a class='trait' href='window/trait.OpenGLWindow.html' title='window::OpenGLWindow'>OpenGLWindow</a> for <a class='struct' href='glutin_window/struct.GlutinWindow.html' title='glutin_window::GlutinWindow'>GlutinWindow</a>",];implementors["piston_window"] = ["impl <a class='trait' href='window/trait.OpenGLWindow.html' title='window::OpenGLWindow'>OpenGLWindow</a> for <a class='struct' href='glutin_window/struct.GlutinWindow.html' title='glutin_window::GlutinWindow'>GlutinWindow</a>",];

            if (window.register_implementors) {
                window.register_implementors(implementors);
            } else {
                window.pending_implementors = implementors;
            }
        
})()
