<?php

function joke_admin() {
  return drupal_get_form('joke_overview_list_page');
}

function joke_overview_list_page($form, &$form_state) {
  // First let's build an add new Joke button
  $form['add_joke'] = [
    '#type' => 'link',
    '#title' => t('Add New Joke'),
    '#href' => 'joke/add',
    '#attributes' => array('class' => array('button', 'action-button')),
    //'#markup' => "<a class='button action-button'>Add New Joke</a>",
  ];

  $headers = [
    'Joke ID',
    'Rating',
    'Joke',
    'Created',
    'Operations'
  ];

  $jokes = [];
  $destination = drupal_get_destination();

  // Now let's grab all the jokes from the database
  $query = db_select('jokes', 'j')->extend('PagerDefault')->extend('TableSort');
  $query->fields('j', array('jid', 'rating', 'value', 'created'));
  $query->orderBy('j.created');
  $query->limit(50);
  $results = $query->execute();

  // We have results!
  if (!empty($results)) {
    foreach ($results as $record) {
      $jokes[$record->jid] = [
        'joke_id' => [
          'data' => [
            '#type' => 'link',
            '#title' => $record->jid,
            '#href' => 'joke/' . $record->jid
          ],
        ],
        'rating' => [
          'data' => [
            '#type' => 'text',
            '#title' => $record->rating,
          ],
        ],
        'joke' => [
          'data' => [
            '#type' => 'text',
            '#value' => $record->value,
          ],
        ],
        'created' => [
          'data' => [
            '#type' => 'text',
            '#value' => format_date($record->created, 'short'),
          ],
        ],
        'operations' => [
          'data' => [
            '#type' => 'link',
            '#title' => t('edit'),
            '#href' => 'joke/' . $record->jid . '/edit',
            '#options' => array('query' => $destination),
          ],
        ]
      ];
    }
  }

  $form['jokes'] = array(
    '#type' => 'tableselect',
    '#header' => $headers,
    '#options' => $jokes,
    '#empty' => t('No jokes available.'),
  );

  $form['pager'] = array('#theme' => 'pager');
}
