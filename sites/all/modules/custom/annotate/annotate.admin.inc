<?php
/**
 * @file
 * Обратные вызовы административной страницы для модуля аннотирования.
 */
/**
 * Создание формы. Настройка аннотирования.
 *
 * @ingroup forms
 * @see system_settings_form().
 */
function annotate_admin_settings() {
  // Получение массива типов нод: ключи — это внутренние имена,
  // а значения — "дружественные имена". Например:
  // array('page' => 'Basic Page', 'article' => 'Articles')
  $types = node_type_get_types();
  foreach ($types as $node_type) {
    $options[$node_type->type] = $node_type->name;
  }
  $form['annotate_node_types'] = [
    '#type' => 'checkboxes',
    '#title' => t('Users may annotate these content types'),
    // Пользователи могут аннотировать эти типы контента
    '#options' => $options,
    '#default_value' => variable_get('annotate_node_types', ['page']),
    '#description' => t('A text field will be available on these content
types to make author-specific notes.'),
    // Для этих типов контента будут доступны текстовые
    // поля, предназначенные для авторских заметок
  ];

  $form['#submit'][] = 'annotate_admin_settings_submit';

  return system_settings_form($form, TRUE);
}

/**
 * annotate_admin_settings_validate
 */
function annotate_admin_settings_submit($form, $form_state) {
  // Цикл по всем флажкам типов контента, имеющихся на форме.
  foreach ($form_state['values']['annotate_node_types'] as $key => $value)
  {
    // Если флажок для типа контента сброшен, проверяем,
    // имеется ли у данного типа контента связанное с ним поле аннотации,
    // с помощью функции field_info_instance. Если имеется,
    // нужно удалить поле аннотации, т.к. флажок сброшен.
    if (!$value) {
      $instance = field_info_instance('node', 'annotation', $key);
      if (!empty($instance)) {
        field_delete_instance($instance);
        watchdog("Annotation", "Deleted annotation field from content type: ".$key);
      } // Конец варианта, когда аннотация существует, и ее необходимо удалить.
    } else {
      // Если флажок для типа контента установлен, проверяем, связано ли с данным
      // типом контента поле. Если нет, добавим в тип контента поле аннотации.
      $instance = field_info_instance('node', 'annotation', $key);
      if (empty($instance)) {
        $instance = array(
          'field_name' => 'annotation',
          'entity_type' => 'node',
          'bundle' => $key,
          'label' => t('Annotation'),
          'widget_type' => 'text_textarea_with_summary',
          'settings' => array('display_summary' => TRUE),
          'display' => array(
            'default' => array(
              'type' => 'text_default',
            ),
            'teaser' => array(
              'type' => 'text_summary_or_trimmed',
            ),
          ),
        );
        $instance = field_create_instance($instance);
        watchdog("Annotation", "Added annotation field to content type: ".$key);
      } // Конец варианта, когда поля аннотации нет, и оно добавляется.
    } // Конец оператора if.
  } // Конец оператора foreach.
}
