<?php

/**
 * @file
 * Administrative forms for webform_sidkey
 */

/**
 * Admin form
 */
function webform_sidkey_admin_form($form, &$form_state) {
  $form['webform_sidkey_default_base'] = array(
    '#type' => 'textfield',
    '#title' => t('Default base encode value'),
    '#description' => t('The base to convert submission ID numbers to. Value must be an integer between 2 and 36.'),
    '#size' => 7,
    '#maxlength' => 2,
    '#default_value' => variable_get('webform_sidkey_default_base', WEBFORM_SIDKEY_DEFAULT_BASE),
    '#element_validate' => array('element_validate_integer_positive'),
    '#required' => TRUE,
    '#access' => user_access('configure webform_sidkey'),
  );

  $form['#validate'][] = '_webform_sidkey_admin_form_validate';

  return system_settings_form($form);
}

/**
 * Ensure the base value is valid
 */
function _webform_sidkey_admin_form_validate(&$form, &$form_state) {
  if (isset($form_state['values']['webform_sidkey_default_base'])) {
    // We trust the element validation to check the basic number stuff. We just care
    // about the value range.
    if (intval($form_state['values']['webform_sidkey_default_base']) > 32 or intval($form_state['values']['webform_sidkey_default_base']) < 2) {
      form_set_error('webform_sidkey_default_base', t('Number out of range. Only values between (and including) 2 and 32 are allowed.'));
    }
  }
}