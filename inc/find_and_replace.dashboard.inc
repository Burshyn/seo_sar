<?php

/**
 * Выводим статистику измененных урлов.
 */
function find_and_replace_dashboard($form, &$form_state)
{
	$form = [];

	$form['from'] = [
		'#type' => 'item',
		'#markup' => l('Search and replace links', '/admin/config/services/find_replace/sar', ['attributes' => ['class' => 'btn btn-primary']]),
	];

	// Формируем результат
	$header = [
		['data' => t('Time'), 'field' => 'time', 'sort' => 'desc'],
		['data' => t('Type'), 'field' => 'type'],
		['data' => t('ID entity'), 'field' => 'id_entity'],
		['data' => t('Searched'), 'field' => 'searched'],
		['data' => t('Replaced'), 'field' => 'replaced'],
	];

	$query = db_select('find_and_replace_stats', 'row')->extend('TableSort');
	$query->fields('row', ['id_entity', 'time', 'type', 'searched', 'replaced', ]);
	$query->orderByHeader($header);
	$result = $query->execute()->fetchAll();

	// Формируем результаты
	$rows = [];
	foreach ($result as $record) {

		// Формируем массив для вывода таблицы
		$rows[] = [
			[
				'data' => date('d-m-Y, h:i:s', $record->time),
				'class' => ['time']
			],
			[
				'data' => $record->type,
				'class' => ['type']
			],
			[
				'data' => $record->id_entity,
				'class' => ['id_entity']
			],
			[
				'data' => $record->searched,
				'class' => ['searched']
			],
			[
				'data' => $record->replaced,
				'class' => ['replaced']
			],
		];


	}

	$form['results'] = [
		'#type' => 'fieldset',
		'#title' => '',
		'#weight' => 5,
		'#collapsible' => FALSE,
		'#collapsed' => FALSE,
	];

	$form['results']['stats_table'] = [
		'#theme' => 'table',
		'#header' => $header,
		'#rows' => $rows,
		'#empty' => t('No access.'),
		'#attributes' => ['class' => ['table', 'mb-0']]
	];

	return $form;
}