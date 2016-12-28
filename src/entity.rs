use body;
use committer;

pub trait Entity<'a> {
    fn body() -> Option<&'a body::Body>;
    fn committer() -> Option<&'a committer::Committer<'a>>;
}
