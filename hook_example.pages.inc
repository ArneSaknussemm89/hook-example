<?php

function joke_edit($jid) {
  $joke = get_joke_by_id($jid);
  $output = drupal_get_form('joke_edit_form', $joke);

  return $output;
}

function joke_add_form($form, &$form_state) {
  $form['title'] = [
    '#type' => 'markup',
    '#markup' => "<h2 class='full-width'>Joke Add Form</h2>",
    '#weight' => 0
  ];

  $form['value'] = [
    '#type' => 'textarea',
    '#description' => t('Tell your joke above! No super long jokes because nobody cares about your jokes.'),
    '#title' => t('Tell Joke Here'),
    '#rows' => 3,
    '#cols' => 70,
    '#default_value' => isset($form_state['values']['value']) ? $form_state['values']['value'] : '',
    '#weight' => 1
  ];

//  $form['actions']['submit'] = [
//    '#type' => 'submit',
//    '#submit' => array('joke_add_submit'),
//    '#value' => t('Add Joke'),
//    '#weight' => 50
//  ];

  return $form;
}

function joke_add_form_submit($form, &$form_state) {

}

/**
 * Form constructor for the node joke confirmation form.
 *
 * @see joke_delete_confirm_submit()
 */
function joke_delete_confirm($form, &$form_state, $joke) {
  $form['#joke'] = $joke;
  // Always provide entity id in the same form key as in the entity edit form.
  $form['jid'] = array('#type' => 'value', '#value' => $joke->jid);
  return confirm_form($form,
    t('Are you sure you want to delete %title?', array('%title' => $joke->value)),
    'joke/' . $joke->jid,
    t('This action cannot be undone.'),
    t('Delete'),
    t('Cancel')
  );
}

/**
 * Executes joke deletion.
 *
 * @see joke_delete_confirm()
 */
function joke_delete_confirm_submit($form, &$form_state) {
  if ($form_state['values']['confirm']) {
    $joke = node_load($form_state['values']['jid']);
    joke_delete($form_state['values']['jid']);
    cache_clear_all();
    watchdog('content', 'Joke: deleted %title.', array('%title' => $joke->value));
    drupal_set_message(t('Joke %title has been deleted.', array('%title' => $joke->value)));
  }

  $form_state['redirect'] = '<front>';
}