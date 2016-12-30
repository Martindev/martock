#![cfg(test)]

use render::window::Window;

struct Test {
    input: (f64, f64),
    expected: Window,
}

#[test]
fn map() {
    for t in vec![Test {
                      input: (0.0, 0.0),
                      expected: Window {
                          x: 0,
                          y: 0,
                          translate_x: 0.0,
                          translate_y: 0.0,
                      },
                  },
                  Test {
                      input: (-0.4, 0.0),
                      expected: Window {
                          x: -1,
                          y: 0,
                          translate_x: -0.6,
                          translate_y: 0.0,
                      },
                  }]
        .iter() {
        assert_eq!(Window::new(t.input.0, t.input.1), t.expected)
    }
}
