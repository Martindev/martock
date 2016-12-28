mod arbiter;
mod block;
mod body;
mod commit;
mod committer;
mod life;
mod reality;
mod tool;
mod world;
mod world_test;

struct Sentience<'a> {
    bodies: Vec<&'a body::Body>,
    committers: Vec<&'a committer::Committer>,
    living: Vec<&'a mut life::Life>,
}

fn engine(a: arbiter::Arbiter,
          r: reality::Reality,
          mut w: world::World,
          mut sentience: Sentience) {
    loop {
        let mut cls = Vec::new();
        for c in sentience.committers.iter() {
            if let Some(cl) = c.cl(&w, &sentience.bodies) {
                cls.push(cl);
            }
        }

        a.arbitrate(&mut w, cls.as_slice());
        r.apply(&w, sentience.bodies.as_mut_slice());

        for mut life in sentience.living.iter_mut() {
            life.update(&w, &sentience.bodies);
        }
    }
}

fn main() {
    let a = arbiter::Arbiter::new();
    let r = reality::Reality::new();
    let w = world::World::new();
    let s = Sentience {
        bodies: Vec::new(),
        committers: Vec::new(),
        living: Vec::new(),
    };
    engine(a, r, w, s);
}
