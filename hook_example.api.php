<?php

/**
 * This hook will allow other modules to react to us creating a new Joke
 * and manipulate it before it is saved.
 */
function hook_joke_presave($joke) {
  $joke->value = "How do you catch a unique rabbit? Unique up on him!";
}