#ifndef __FORCES_H__
#define __FORCES_H__

#include "scene.h"

/**
 * A function called when a collision occurs.
 * @param body1 the first body passed to create_collision()
 * @param body2 the second body passed to create_collision()
 * @param axis a unit vector pointing from body1 towards body2
 *   that defines the direction the two bodies are colliding in
 * @param aux the auxiliary value passed to create_collision()
 */
typedef void (*collision_handler_t)
    (body_t *body1, body_t *body2, vector_t axis, void *aux);

    
typedef struct collision_package {
   void *aux;
   collision_handler_t handler;
   free_func_t freer;
   list_t *bodies;
   bool collided;
} collision_package_t;

/**
 * Adds a force creator to a scene that applies a gravitational force acting downward.
 * The force creator will be called each tick
 *
 * @param scene the scene containing the bodies
 * @param G the gravitational acceleration constant
 * @param body1 the first body
 * @param body2 the second body
 */
void create_downward_gravity(scene_t *scene, double G, body_t *body);

/**
 * Adds a force creator to a scene that applies a magnetic force acting one one object.
 * The force creator will be called each tick
 *
 * @param scene the scene containing the bodies
 * @param M the magnetic acceleration constant
 * @param body1 the first body
 * @param body2 the second body
 */
void create_magnetic_force(scene_t *scene, double M, body_t *body1, body_t *body2);

/**
 * Adds a force creator to a scene that calls a given collision handler
 * function each time two bodies collide.
 * This generalizes create_destructive_collision() from last week,
 * allowing different things to happen on a collision.
 * The handler is passed the bodies, the collision axis, and an auxiliary value.
 * It should only be called once while the bodies are still colliding.
 *
 * @param scene the scene containing the bodies
 * @param body1 the first body
 * @param body2 the second body
 * @param handler a function to call whenever the bodies collide
 * @param aux an auxiliary value to pass to the handler
 * @param freer if non-NULL, a function to call in order to free aux
 */
void create_collision(
    scene_t *scene,
    body_t *body1,
    body_t *body2,
    collision_handler_t handler,
    void *aux,
    free_func_t freer,
    force_creator_t collided
);

/**
 * Adds a force creator to a scene that destroys two bodies when they collide.
 * The bodies should be destroyed by calling body_remove().
 * This should be represented as an on-collision callback
 * registered with create_collision().
 *
 * @param scene the scene containing the bodies
 * @param body1 the first body
 * @param body2 the second body
 */
void create_destructive_collision(scene_t *scene, body_t *body1, body_t *body2);

/**
 * Adds a force creator to a scene that applies impulses
 * to resolve collisions between two bodies in the scene.
 * This should be represented as an on-collision callback
 * registered with create_collision().
 *
 * @param scene the scene containing the bodies
 * @param elasticity the "coefficient of restitution" of the collision;
 * 0 is a perfectly inelastic collision and 1 is a perfectly elastic collision
 * @param body1 the first body
 * @param body2 the second body
 */
void create_platform_collision(scene_t *scene, double elasticity, body_t *body1, body_t *body2);

/**
 * Adds a force creator to a scene that registers the collision between the character and a magnet or immunity 
 * powerup and equips the powerup. The force creator will be called each tick
 *
 * @param scene the scene containing the bodies
 * @param elacticity the elasticity of the collision between the two bodies
 * @param body1 the first body
 * @param body2 the second body
 */
void create_powerup_collision(scene_t *scene, double elasticity, body_t *body1, body_t *body2);

/**
 * Adds a force creator to a scene that gives the character immunity by killing all enemies that
 * collide with the immunity shield. The force creator will be called each tick
 *
 * @param scene the scene containing the bodies
 * @param elacticity the elasticity of the collision between the two bodies
 * @param body1 the first body
 * @param body2 the second body
 */
void create_immunity_collision(scene_t *scene, double elasticity, body_t *body1, body_t *body2);

/**
 * Adds a force creator to a scene that registers the collision between the character and a boost powerup
 * and equips the powerup. The force creator will be called each tick
 *
 * @param scene the scene containing the bodies
 * @param elacticity the elasticity of the collision between the two bodies
 * @param body1 the first body
 * @param body2 the second body
 */
void create_boost_collision(scene_t *scene, double elasticity, body_t *body1, body_t *body2);

/**
 * Adds a force creator to a scene that removes the star when the player collides with it.
 *
 * @param scene the scene containing the bodies
 * @param elasticity elasticity for force aux
 * @param body1 the first body
 * @param body2 the second body
 */
void create_star_collision(scene_t *scene, double elasticity, body_t *body1, body_t *body2);

#endif // #ifndef __FORCES_H__