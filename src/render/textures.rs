//! textures provides textures for elements of the world.

use graphics::types::Color;

use block::Block;

/// block returns a texture for the given block. At the moment this is just a color.
/// TODO(turnage): Implement loading textures for blocks and initializing Renderer with this
/// resource.
pub fn block(b: Option<Block>) -> Color {
    match b {
        None => [0.0, 0.0, 1.0, 1.0],
        Some(Block::Ether) => [0.2, 0.2, 0.2, 1.0],
        Some(Block::Void) => [1.0, 0.0, 0.0, 1.0], // This should not happen.
    }
}
