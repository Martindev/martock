//! world defines the martock world frontend.

/// Loads a world implementation.
pub trait WorldLoader<T: World> {
    fn world(&self) -> T;
}

pub trait World {}
