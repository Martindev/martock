use block;
use world;

/// BlockIter iterates over a rectangle of blocks in the world.
pub struct BlockIter<'a> {
    x: i64,
    y: u8,
    start_x: i64,
    end_x: i64,
    end_y: u8,
    world: &'a world::World,
}

impl<'a> BlockIter<'a> {
    pub fn new(x: i64, y: u8, width: usize, height: usize, world: &'a world::World) -> Self {
        BlockIter {
            x: x,
            y: y,
            start_x: x,
            end_x: x + width as i64,
            end_y: y + height as u8,
            world: world,
        }
    }
}

impl<'a> Iterator for BlockIter<'a> {
    type Item = (i64, u8, block::Block);
    
    /// next provides a tuple of (x, y, Option<Block>) until the window is spent.
    fn next(&mut self) -> Option<Self::Item> {
        if self.x < self.end_x && self.y < self.end_y {
            let block = Some((self.x, self.y, self.world.block(self.x, self.y)));
            self.x = if self.x >= self.end_x - 1 {
                self.y += 1;
                self.start_x
            } else {
                self.x + 1
            };
            block
        } else {
            None
        }
    }
}
