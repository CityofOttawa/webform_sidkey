<?php

/**
 * @file
 * User facing pages
 */

/**
 * Page callback for loading submission
 */
function webform_sidkey_lookup_page($form, &$form_state, $webform) {
  $form_state['sidkey_form'] = $webform;

  $form['webform_sidkey_key'] = array(
    '#title' => t('Type in your submission key'),
    '#required' => TRUE,
    '#type' => 'textfield',
    '#size' => 20,
  );

  $form['submit'] = array(
    '#type' => 'submit',
    '#title' => t('Continue'),
    '#value' => t('Continue'),
  );

  $form['#submit'][] = 'webform_sidkey_report_form_submit';
  $form['#validate'][] = 'webform_sidkey_report_form_validate';

  return $form;
}

/**
 * Report validation callback
 */
function webform_sidkey_report_form_validate(&$form, &$form_state) {
  $values = $form_state['values'];
  $submission = webform_sidkey_get_submissions(array('sidkey' => $values['webform_sidkey_key'], 'nid' => $form_state['sidkey_form']->nid));

  if (empty($submission)) {
    form_set_error('webform_sidkey_key', t('Submission key not found. Please verify the value.'));
  }
}

/**
 * Report for submit callback
 */
function webform_sidkey_report_form_submit(&$form, &$form_state) {
  // Load the submission via the submission key
  $submission = webform_sidkey_get_submissions(array('sidkey' => $form_state['values']['webform_sidkey_key'], 'nid' => $form_state['sidkey_form']->nid));
  $submission = reset($submission);

  // Go to URL
  drupal_goto('node/' . $form_state['sidkey_form']->nid . '/submission/' . $submission->sid);
}