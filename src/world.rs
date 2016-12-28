//! world defines the martock world frontend.

/// Loads a world implementation.
pub trait WorldLoader {
    fn world() -> World;
}

pub trait World {}
