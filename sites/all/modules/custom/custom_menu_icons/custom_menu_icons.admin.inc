<?php

/**
 * Creating form menu icons settings
 *
 * @ingroup forms
 * @see system_settings_form().
 */
function custom_menu_icons_admin_settings() {

  $menus = menu_get_menus();

  foreach ($menus as $menu_name => $menu_title) {
    $options[$menu_name] = $menu_title;
  }

  $form['custom_menu_icons_menus'] = [
    '#type' => 'checkboxes',
    '#title' => t('Users may add icons for menu items'),
    '#options' => $options,
    '#default_value' => variable_get('custom_menu_icons_menus', []),
    '#description' => t('Icons will be available on these menus.'),
  ];

  $form['custom_menu_icons_icons'] = [
    '#type' => 'textarea',
    '#title' => t('LIst of icons'),
    '#default_value' => variable_get('custom_menu_icons_icons', []),
    '#description' => t('List of icons that you will select on menu item edit form.<br/>'
                              .'The possible values this field can contain. Enter one value per line, in the format key|label.<br/>'
                              .'The key is the stored value. The label will be used in displayed values and edit forms.'),
  ];

  $form['#submit'][] = 'custom_menu_icons_admin_settings_submit';

  return system_settings_form($form, TRUE);
}

function custom_menu_icons_admin_settings_submit($form, $form_state) {

}

function custom_menu_icons_admin_settings_validate($form, $form_state) {

}
