#![cfg(test)]

use camera::View;

struct ViewTest {
    input: (f64, f64, usize, usize),
    expected: View,
}

#[test]
fn view() {
    for t in vec![ViewTest {
                      input: (0.0, 0.0, 10, 12),
                      expected: View {
                          width: 10,
                          height: 12,
                          block_x: 0,
                          block_y: 0,
                          translate_x: 0.0,
                          translate_y: 0.0,
                      },
                  },
                  ViewTest {
                      input: (-0.4, 0.0, 200, 600),
                      expected: View {
                          width: 200,
                          height: 600,
                          block_x: -1,
                          block_y: 0,
                          translate_x: -0.6,
                          translate_y: 0.0,
                      },
                  }]
        .iter() {
        assert_eq!(Window::new(t.input.0, t.input.1), t.expected)
    }
}
