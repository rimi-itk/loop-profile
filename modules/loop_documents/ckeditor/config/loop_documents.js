var LoopDocuments = {
		createTableTemplate: function(config) {
				var i, j;
				var content = [];

				content.push('<table' + (config.classNames ? ' class="' + config.classNames.join(' ') + '"' : '') + '>');
				if (config.heads) {
						content.push('<thead>');
						for (i = 0; i < config.heads.length; i++) {
								content.push('<tr>');
								for (j = 0; j < config.heads[i].length; j++) {
										content.push('<th>' + config.heads[i][j] + '</th>');
								}
								content.push('</tr>');
						}
						content.push('</thead>');
				}
				if (config.foots) {
						content.push('<tfoot>');
						for (i = 0; i < config.foots.length; i++) {
								content.push('<tr>');
								for (j = 0; j < config.foots[i].length; j++) {
										content.push('<td>' + config.foots[i][j] + '</td>');
								}
								content.push('</tr>');
						}
						content.push('</tfoot>');
				}
				if (config.rows) {
						content.push('<tbody>');
						for (i = 0; i < config.rows.length; i++) {
								content.push('<tr>');
								for (j = 0; j < config.rows[i].length; j++) {
										content.push('<td>' + config.rows[i][j] + '</td>');
								}
								content.push('</tr>');
						}
						content.push('</tbody>');
				}
				content.push('</table>');

				return content.join('');
		}
};

CKEDITOR.addTemplates('loop_documents', {
		// The name of the subfolder that contains the preview images of the templates.
		// imagesPath : CKEDITOR.getUrl( CKEDITOR.plugins.getPath( 'templates' ) + 'templates/images/' ),

		// Template definitions.
		templates: [
				{
						title: 'Trin – Handling',
						description: 'Indsæt tabel med "Trin – Handling".',
						html: LoopDocuments.createTableTemplate({
								classNames: ['loop-documents-table', 'loop-documents-table-steps'],
								heads: [
										['Trin', 'Handling'],
								],
								rows: [
										[1, ''],
										[2, ''],
										[3, ''],
										[4, ''],
										[5, ''],
								]
						})
				}, {
						title: 'Trin – Handling – Illustration',
						description: 'Indsæt tabel med "Trin – Handling – Illustration".',
						html: LoopDocuments.createTableTemplate({
								classNames: ['loop-documents-table', 'loop-documents-table-steps'],
								heads: [
										['Trin', 'Handling', 'Illustration']
								],
								rows: [
										[1, '', ''],
										[2, '', ''],
										[3, '', ''],
										[4, '', ''],
										[5, '', ''],
								]
						})
				}, {
						title: 'Fase – Beskrivelse – Link',
						description: 'Indsæt tabel med "Fase – Beskrivelse – Link".',
						html: LoopDocuments.createTableTemplate({
								classNames: ['loop-documents-table', 'loop-documents-table-steps'],
								heads: [
										['Fase', 'Beskrivelse', 'Link']
								],
								rows: [
										[1, '', ''],
										[2, '', ''],
										[3, '', ''],
										[4, '', ''],
										[5, '', ''],
								]
						})
				}, {
						title: 'Tabel med to kolonner',
						description: 'Indsæt tabel med to kolonner.',
						html: LoopDocuments.createTableTemplate({
								classNames: ['loop-documents-table'],
								heads: [
										['', '']
								],
								rows: [
										['', ''],
										['', ''],
										['', ''],
										['', ''],
										['', ''],
								]
						})
				}, {
						title: 'Tabel med tre kolonner',
						description: 'Indsæt tabel med tre kolonner.',
						html: LoopDocuments.createTableTemplate({
								classNames: ['loop-documents-table'],
								heads: [
										['', '', '']
								],
								rows: [
										['', '', ''],
										['', '', ''],
										['', '', ''],
										['', '', ''],
										['', '', ''],
								]
						})
				}
		]
});

CKEDITOR.stylesSet.add('loop_documents', []);

CKEDITOR.editorConfig = function (config) {
		config.skin = 'moono';

		config.toolbar = [
				[ 'Format', '-', 'Bold', '-', 'NumberedList', 'BulletedList', '-', 'Outdent', 'Indent' ],
				[ 'Link', 'Unlink' ],
				[ 'media', 'mediaBrowser' ],
				[ 'Templates' ],
				[ 'RemoveFormat' ],
				[ 'Source' ]
		];

		// Allow body text (p) and two heading levels (h2, h3)
		config.format_tags = 'p;h2;h3';

		config.stylesSet = 'loop_documents';
		config.templates = 'loop_documents';
		config.templates_replaceContent = false;
};
