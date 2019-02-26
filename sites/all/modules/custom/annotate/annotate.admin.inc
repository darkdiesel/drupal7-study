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
  return system_settings_form($form, TRUE);
}
